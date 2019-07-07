#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomCardTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
RandomCardTask::RandomCardTask(CardType cardType, CardClass cardClass, Race cardRace)
    : m_cardTypes({ cardType }), m_cardClasses({ cardClass} ), m_cardRaces({ cardRace })
{
    // Do nothing
}

RandomCardTask::RandomCardTask(
    std::vector<CardType> cardTypes,
    std::vector<CardClass> cardClasses,
    std::vector<Race> cardRaces)
    : m_cardTypes(cardTypes), m_cardClasses(cardClasses), m_cardRaces(cardRaces)
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
    std::vector<RosettaStone::Card> filtered(allCards.size());

    if (m_cardTypes.empty())
    {
        return TaskStatus::STOP;
    }

    const bool passClassCheck = (m_cardClasses.empty() || m_cardClasses[0] == CardClass::INVALID);
    const bool passRaceCheck = (m_cardRaces.empty() || m_cardRaces[0] == Race::INVALID);

    auto filter = [&](const Card& card) -> bool{
        
        if (card.gameTags.at(GameTag::COLLECTIBLE) != 1)
        {
            return false;
        }

        if (std::find(m_cardTypes.begin(), m_cardTypes.end(), card.GetCardType()) == m_cardTypes.end())
        {
            return false;
        }

        if (!passClassCheck &&
            std::find(m_cardClasses.begin(), m_cardClasses.end(), card.GetCardClass()) == m_cardClasses.end())
        {
            return false;
        }

        if (!passRaceCheck &&
            std::find(m_cardRaces.begin(), m_cardRaces.end(), card.GetRace()) == m_cardRaces.end())
        {
            return false;
        }

        return true;
    };

    const auto end = std::copy_if(allCards.begin(), allCards.end(), filtered.begin(), filter);
    filtered.resize(std::distance(filtered.begin(), end));

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
