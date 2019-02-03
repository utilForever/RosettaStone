// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Cards/Entity.hpp>
#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Weapon.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Commons/Utils.hpp>
#include <hspp/Models/GameAgent.hpp>
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

TaskStatus DrawTask::Impl(Player& player)
{
    size_t num = m_num;
    TaskStatus result = TaskStatus::DRAW_SUCCESS;

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
        result = TaskStatus::DRAW_EXHAUST;
    }

    // When hand size over MAXIMUM_NUM_CARDS_IN_HAND, overdraw
    if (hand.size() + num > MAXIMUM_NUM_CARDS_IN_HAND)
    {
        // The number of overdraw
        const size_t over = hand.size() + num - MAXIMUM_NUM_CARDS_IN_HAND;

        Box<Entity*> burnt(over);

        // Draw burnt card
        for (size_t i = 0; i < over; ++i)
        {
            burnt[i] = deck.back();
            deck.pop_back();
        }

        num = MAXIMUM_NUM_CARDS_IN_HAND - hand.size();

        if (result == TaskStatus::DRAW_EXHAUST)
        {
            result = TaskStatus::DRAW_EXHAUST_OVERDRAW;
        }
        else
        {
            result = TaskStatus::DRAW_OVERDRAW;
        }

        // Send burnt cards to policy
        TaskMetaTrait trait(TaskID::DRAW, TaskStatus::DRAW_OVERDRAW,
                            player.GetID());
        player.GetPolicy().Notify(TaskMeta(trait, std::move(burnt)));
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

TaskStatus DrawCardTask::Impl(Player& player)
{
    std::vector<Entity*>& deck = player.GetDeck();
    std::vector<Entity*>& hand = player.GetHand();

    switch (m_card.cardType)
    {
        case +CardType::MINION:
            hand.emplace_back(new Minion(m_card));
            break;
        case +CardType::WEAPON:
            hand.emplace_back(new Weapon(m_card));
            break;
        default:
            hand.emplace_back(new Entity(m_card));
    }

    if (!deck.empty())
    {
        deck.pop_back();
    }

    return TaskStatus::DRAW_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks