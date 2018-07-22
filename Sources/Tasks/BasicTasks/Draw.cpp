/*************************************************************************
> File Name: Draw.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/Draw.h>

#include <Cards/Entity.h>

namespace Hearthstonepp::BasicTasks
{
DrawTask::DrawTask(size_t num, TaskAgent& agent) : m_num(num), m_agent(agent)
{
    // Do Nothing
}

TaskID DrawTask::GetTaskID() const
{
    return TaskID::DRAW;
}

MetaData DrawTask::Impl(Player& user, Player&) const
{
    size_t num = m_num;
    MetaData result = MetaData::DRAW_SUCCESS;

    std::vector<Entity*>& deck = user.cards;
    std::vector<Entity*>& hand = user.hand;

    // when deck is exhausted
    if (deck.size() < num)
    {
        size_t rest = num - deck.size();

        // sigma (i = 1 to rest) { current.exhausted + i }
        int hurts =
            static_cast<int>(user.exhausted * rest + rest * (rest + 1) / 2);
        int hurted = static_cast<int>(user.hero->health) - hurts;

        user.hero->health = hurted > 0 ? static_cast<size_t>(hurted) : 0;
        user.exhausted += static_cast<BYTE>(rest);

        // full draw is fail
        result = MetaData::DRAW_EXHAUST;
    }

    // when hand size over 10, over draw
    if (hand.size() + num > 10)
    {
        // number of over draw
        size_t over = hand.size() + num - 10;

        std::vector<Entity*> burnt;
        burnt.reserve(over);

        // draw burnt card
        for (size_t i = 0; i < over; ++i)
        {
            burnt.emplace_back(deck.back());
            deck.pop_back();
        }

        num = 10 - hand.size();

        // draw is fail
        if (result == MetaData::DRAW_EXHAUST)
        {
            result = MetaData::DRAW_EXHAUST_OVERDRAW;
        }
        else
        {
            result = MetaData::DRAW_OVERDRAW;
        }

        TaskMetaTrait trait(TaskID::OVER_DRAW, result, user.id);
        m_agent.Notify(Serializer::CreateEntityVector(trait, burnt));
    }

    // successful draw
    for (size_t i = 0; i < num; ++i)
    {
        hand.push_back(deck.back());
        deck.pop_back();
    }

    return result;
}

DrawCardTask::DrawCardTask(Card* card)
{
    switch (card->cardType)
    {
        case +CardType::MINION:
            m_entity = new Minion(card);
            break;
        case +CardType::WEAPON:
            m_entity = new Weapon(card);
            break;
        default:
            m_entity = new Entity(card);
    }
}

TaskID DrawCardTask::GetTaskID() const
{
    return TaskID::DRAW;
}

MetaData DrawCardTask::Impl(Player& user, Player&) const
{
    std::vector<Entity*>& deck = user.cards;
    std::vector<Entity*>& hand = user.hand;

    hand.emplace_back(m_entity);
    if (!deck.empty())
    {
        deck.pop_back();
    }

    return MetaData::DRAW_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks