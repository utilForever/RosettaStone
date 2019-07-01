#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <iostream>
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
    std::vector<RosettaStone::Card> filtered;

    switch (m_cardType)
    {
        case CardType::MINION:
        case CardType::SPELL:
        case CardType::INVALID:
            break;
        default:
            throw std::invalid_argument(
                "RandomCardTask::Impl() - Invalid card type!");
    }
    
    for (auto card : allCards)
    {
        if (((m_cardType == CardType::INVALID && m_cardType == CardType::MINION
                && m_cardType == CardType::SPELL || m_cardType == card.GetCardType())) &&
             (m_cardClass == CardClass::INVALID || m_cardClass == card.GetCardClass()) &&
             (m_cardRace == Race::INVALID || m_cardRace == card.GetRace()))
        {
            filtered.emplace_back(card);
        }
    }

    if (filtered.empty())
    {
        return TaskStatus::STOP;
    }
    
    const auto idx = Random::get<std::size_t>(0, filtered.size() - 1);
    Card& card = filtered.at(idx);
    
    Entity* entity = Entity::GetFromCard(player, std::move(card));
    
    player.GetGame()->taskStack.entities.clear();
    player.GetGame()->taskStack.entities.emplace_back(entity);

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
