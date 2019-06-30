#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Actions/Generic.hpp>

#include <Rosetta/Tasks/SimpleTasks/RandomCardTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
RandomCardTask::RandomCardTask(CardType cardType, CardClass cardClass, Race cardRace)
    : m_cardType(cardType), m_cardClass(cardClass), m_cardRace(cardRace)
{
    // Do nothing
}

TaskID RandomCardTask::GetTaskID() const
{
    return TaskID::RANDOM_CARD;
}

TaskStatus RandomCardTask::Impl(Player& player)
{
    const auto allCards = Cards::GetInstance().GetAllCards();
    const auto filtered = new std::vector<RosettaStone::Card>();

    for (auto card : allCards)
    {
        if (card.GetCardType() == m_cardType && card.GetCardClass() == m_cardClass && card.GetRace() == m_cardRace)
        {
            filtered->emplace_back(card);
        }
    }

    if (filtered->empty())
    {
        return TaskStatus::STOP;
    }

    const auto idx = Random::get<std::size_t>(0, filtered->size() - 1);
    auto card = filtered->at(idx);

    Entity* entity = Entity::GetFromCard(player, std::move(card));
    
    player.GetGame()->taskStack.entities.clear();
    player.GetGame()->taskStack.entities.emplace_back(entity);
    
    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
