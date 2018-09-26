#include <Tasks/BasicTasks/DrawTask.h>

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

MetaData DrawTask::Impl(Player& user, Player&)
{
    size_t num = m_num;
    MetaData result = MetaData::DRAW_SUCCESS;

    std::vector<Entity*>& deck = user.cards;
    std::vector<Entity*>& hand = user.hand;

    // after reaching fatigue
    if (deck.size() < num)
    {
        size_t numDrawAfterFatigue = num - deck.size();

        // sigma (i = 1 to numDrawAfterFatigue) { current.exhausted + i }
        int fatigueDamage = static_cast<int>(
            user.exhausted * numDrawAfterFatigue +
            numDrawAfterFatigue * (numDrawAfterFatigue + 1) / 2);
        int remainHealth = static_cast<int>(user.hero->health) - fatigueDamage;

        user.hero->health =
            remainHealth > 0 ? static_cast<size_t>(remainHealth) : 0;
        user.exhausted += static_cast<BYTE>(numDrawAfterFatigue);

        num = deck.size();
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

        if (result == MetaData::DRAW_EXHAUST)
        {
            result = MetaData::DRAW_EXHAUST_OVERDRAW;
        }
        else
        {
            result = MetaData::DRAW_OVERDRAW;
        }

        // Send Burnt Cards to GameInterface
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

DrawCardTask::DrawCardTask(const Card* card)
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

MetaData DrawCardTask::Impl(Player& user, Player&)
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