#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomCardTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
RandomCardTask::RandomCardTask(EntityType entityType, bool opposite)
    : ITask(entityType),
      m_cardType(CardType::INVALID),
      m_cardClass(CardClass::INVALID),
      m_race(Race::INVALID),
      m_opposite(opposite)
{
    // Do nothing
}

RandomCardTask::RandomCardTask(CardType cardType, CardClass cardClass,
                               Race race, bool opposite)
    : m_cardType(cardType),
      m_cardClass(cardClass),
      m_race(race),
      m_opposite(opposite)
{
    // Do nothing
}

std::vector<Card*> RandomCardTask::GetCardList(CardType cardType,
                                               CardClass cardClass, Race race)
{
    std::vector<Card*> result;
    const auto cards = Cards::GetAllCards();

    for (const auto& card : cards)
    {
        if ((cardType == CardType::INVALID ||
             cardType == card->GetCardType()) &&
            (cardClass == CardClass::INVALID ||
             cardClass == card->GetCardClass()) &&
            (race == Race::INVALID || race == card->GetRace()))
        {
            result.emplace_back(card);
        }
    }

    return result;
}

TaskStatus RandomCardTask::Impl(Player* player)
{
    auto cardsList = GetCardList(m_cardType, m_cardClass, m_race);
    if (cardsList.empty())
    {
        return TaskStatus::STOP;
    }

    const auto idx = Random::get<std::size_t>(0, cardsList.size() - 1);
    auto randomCard = Entity::GetFromCard(
        m_opposite ? player->opponent : player, cardsList.at(idx));
    player->game->taskStack.playables.emplace_back(randomCard);

    return TaskStatus::COMPLETE;
}

ITask* RandomCardTask::CloneImpl()
{
    return new RandomCardTask(m_cardType, m_cardClass, m_race);
}
}  // namespace RosettaStone::SimpleTasks
