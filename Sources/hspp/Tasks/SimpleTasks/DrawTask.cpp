// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Cards/Entity.hpp>
#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Weapon.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>

#include <utility>

namespace Hearthstonepp::SimpleTasks
{
DrawTask::DrawTask(size_t num) : m_num(num)
{
    // Do nothing
}

TaskID DrawTask::GetTaskID() const
{
    return TaskID::DRAW;
}

MetaData DrawTask::Impl(Player& player)
{
    size_t num = m_num;
    MetaData result = MetaData::DRAW_SUCCESS;

    std::vector<Entity*>& deck = player.GetDeck();
    std::vector<Entity*>& hand = player.GetHand();

    // After reaching fatigue
    if (deck.size() < num)
    {
        const size_t numDrawAfterFatigue = num - deck.size();

        // Sigma (i = 1 to numDrawAfterFatigue) { current.exhausted + i }
        const auto fatigueDamage = static_cast<int>(
            player.GetNumCardAfterExhaust() * numDrawAfterFatigue +
            numDrawAfterFatigue * (numDrawAfterFatigue + 1) / 2);

        player.GetHero()->health = player.GetHero()->health - fatigueDamage;
        player.SetNumCardAfterExhaust(static_cast<BYTE>(
            player.GetNumCardAfterExhaust() + numDrawAfterFatigue));

        num = deck.size();
        result = MetaData::DRAW_EXHAUST;
    }

    // When hand size over HAND_SIZE, overdraw
    if (hand.size() + num > HAND_SIZE)
    {
        // The number of overdraw
        const size_t over = hand.size() + num - HAND_SIZE;

        std::vector<Entity*> burnt;
        burnt.reserve(over);

        // Draw burnt card
        for (size_t i = 0; i < over; ++i)
        {
            burnt.emplace_back(deck.back());
            deck.pop_back();
        }

        num = HAND_SIZE - hand.size();

        if (result == MetaData::DRAW_EXHAUST)
        {
            result = MetaData::DRAW_EXHAUST_OVERDRAW;
        }
        else
        {
            result = MetaData::DRAW_OVERDRAW;
        }

        // Send burnt cards to GameInterface
        const TaskMetaTrait trait(TaskID::OVERDRAW, result, player.GetID());
        player.GetGameAgent()->NotifyToTaskAgent(
            Serializer::CreateEntityVector(trait, burnt));
    }

    // Draw success
    for (size_t i = 0; i < num; ++i)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }

    return result;
}

DrawCardTask::DrawCardTask(const Card& card) : m_card(card)
{
    // Do nothing
}

DrawCardTask::DrawCardTask(Card&& card) : m_card(std::move(card))
{
    // Do nothing
}

TaskID DrawCardTask::GetTaskID() const
{
    return TaskID::DRAW;
}

MetaData DrawCardTask::Impl(Player& player)
{
    std::vector<Entity*>& deck = player.GetDeck();
    std::vector<Entity*>& hand = player.GetHand();

    auto* gameAgent = player.GetGameAgent();

    switch (m_card.cardType)
    {
        case +CardType::MINION:
            hand.emplace_back(new Minion(gameAgent, m_card));
            break;
        case +CardType::WEAPON:
            hand.emplace_back(new Weapon(gameAgent, m_card));
            break;
        default:
            throw std::invalid_argument(
                "DrawCardTask::Impl() - Invalid card type!");
    }

    if (!deck.empty())
    {
        deck.pop_back();
    }

    return MetaData::DRAW_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks