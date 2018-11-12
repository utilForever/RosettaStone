// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Entity.h>
#include <hspp/Commons/Constants.h>
#include <hspp/Tasks/BasicTasks/DrawTask.h>

#include <utility>

namespace Hearthstonepp::BasicTasks
{
DrawTask::DrawTask(Player& player, size_t num) : m_player(player), m_num(num)
{
    // Do nothing
}

TaskID DrawTask::GetTaskID() const
{
    return TaskID::DRAW;
}

MetaData DrawTask::Impl(Player& user, Player&)
{
    size_t num = m_num;
    MetaData result = MetaData::DRAW_SUCCESS;

    std::vector<Entity*>& deck = user.cards;
    std::vector<Entity*>& hand = user.hand;

    // After reaching fatigue
    if (deck.size() < num)
    {
        const size_t numDrawAfterFatigue = num - deck.size();

        // Sigma (i = 1 to numDrawAfterFatigue) { current.exhausted + i }
        const auto fatigueDamage = static_cast<int>(
            user.exhausted * numDrawAfterFatigue +
            numDrawAfterFatigue * (numDrawAfterFatigue + 1) / 2);
        const int remainHealth =
            static_cast<int>(user.hero->health) - fatigueDamage;

        user.hero->health =
            remainHealth > 0 ? static_cast<size_t>(remainHealth) : 0;
        user.exhausted += static_cast<BYTE>(numDrawAfterFatigue);

        num = deck.size();
        result = MetaData::DRAW_EXHAUST;
    }

    // When hand size over MAXIMUM_NUM_CARDS_IN_HAND, overdraw
    if (hand.size() + num > MAXIMUM_NUM_CARDS_IN_HAND)
    {
        // The number of overdraw
        const size_t over = hand.size() + num - MAXIMUM_NUM_CARDS_IN_HAND;

        std::vector<Entity*> burnt;
        burnt.reserve(over);

        // Draw burnt card
        for (size_t i = 0; i < over; ++i)
        {
            burnt.emplace_back(deck.back());
            deck.pop_back();
        }

        num = MAXIMUM_NUM_CARDS_IN_HAND - hand.size();

        if (result == MetaData::DRAW_EXHAUST)
        {
            result = MetaData::DRAW_EXHAUST_OVERDRAW;
        }
        else
        {
            result = MetaData::DRAW_OVERDRAW;
        }

        // Send burnt cards to GameInterface
        //const TaskMetaTrait trait(TaskID::OVERDRAW, result, user.id);
        //m_agent.Notify(Serializer::CreateEntityVector(trait, burnt));
    }

    // Draw success
    for (size_t i = 0; i < num; ++i)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }

    return result;
}

DrawCardTask::DrawCardTask(Card card) : m_card(std::move(card))
{
    // Do nothing
}

TaskID DrawCardTask::GetTaskID() const
{
    return TaskID::DRAW;
}

MetaData DrawCardTask::Impl(Player& user, Player&)
{
    std::vector<Entity*>& deck = user.cards;
    std::vector<Entity*>& hand = user.hand;

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

    return MetaData::DRAW_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks