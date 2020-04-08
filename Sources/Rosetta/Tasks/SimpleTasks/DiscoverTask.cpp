// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscoverTask.hpp>
#include <Rosetta/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

#include <utility>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
DiscoverCriteria::DiscoverCriteria(CardType _cardType, CardClass _cardClass,
                                   Race _race, Rarity _rarity)
    : cardType(_cardType), cardClass(_cardClass), race(_race), rarity(_rarity)
{
    // Do nothing
}

bool DiscoverCriteria::Evaluate(Card* card) const
{
    return (cardType == CardType::INVALID || cardType == card->GetCardType()) &&
           (race == Race::INVALID || race == card->GetRace()) &&
           (rarity == Rarity::INVALID || rarity == card->GetRarity());
}

DiscoverTask::DiscoverTask(CardType cardType, CardClass cardClass, Race race,
                           Rarity rarity, ChoiceAction choiceAction,
                           bool keepAll)
    : m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction),
      m_keepAll(keepAll)
{
    // Do nothing
}

DiscoverTask::DiscoverTask(const std::vector<std::string>& cardIDs,
                           ChoiceAction choiceAction, int numberOfChoices,
                           bool doShuffle)
    : m_choiceAction(choiceAction),
      m_numberOfChoices(numberOfChoices),
      m_doShuffle(doShuffle)
{
    for (auto& cardID : cardIDs)
    {
        m_cards.emplace_back(Cards::FindCardByID(cardID));
    }
}

DiscoverTask::DiscoverTask(DiscoverType discoverType)
    : m_discoverType(discoverType)
{
    // Do nothing
}

DiscoverTask::DiscoverTask(std::vector<Card*> cards, DiscoverType discoverType,
                           CardType cardType, CardClass cardClass, Race race,
                           Rarity rarity, ChoiceAction choiceAction,
                           int numberOfChoices, bool doShuffle, bool keepAll)
    : m_cards(std::move(cards)),
      m_discoverType(discoverType),
      m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction),
      m_numberOfChoices(numberOfChoices),
      m_doShuffle(doShuffle),
      m_keepAll(keepAll)
{
    // Do nothing
}

std::vector<Card*> DiscoverTask::GetChoices(std::vector<Card*> cardsToDiscover,
                                            std::size_t numberOfChoices) const
{
    std::vector<Card*> result;

    if (numberOfChoices >= cardsToDiscover.size())
    {
        result = cardsToDiscover;
    }
    else
    {
        result.reserve(numberOfChoices);

        if (m_doShuffle)
        {
            std::sample(cardsToDiscover.begin(), cardsToDiscover.end(),
                        std::back_inserter(result), numberOfChoices,
                        Random::get_engine());
        }
        else
        {
            for (std::size_t i = 0; i < numberOfChoices; ++i)
            {
                result[i] = cardsToDiscover[i];
            }
        }
    }

    return result;
}

TaskStatus DiscoverTask::Impl(Player* player)
{
    std::vector<Card*> result;

    if (!m_cards.empty())
    {
        result = GetChoices(m_cards, m_numberOfChoices);
    }
    else if (m_discoverType != DiscoverType::INVALID)
    {
        const auto cardsToDiscover =
            Discover(player->game, player, m_discoverType);
        result = GetChoices(cardsToDiscover, m_numberOfChoices);
    }
    else
    {
        const auto cardsToDiscover =
            Discover(player->game, player, m_discoverCriteria);
        result = GetChoices(cardsToDiscover, m_numberOfChoices);
    }

    if (result.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_keepAll)
    {
        for (std::size_t i = 0;
             i < result.size() && !player->GetHandZone()->IsFull(); ++i)
        {
            const auto entity = Entity::GetFromCard(
                player, result[i], std::nullopt, player->GetHandZone());
            Generic::AddCardToHand(player, entity);
        }
    }

    Generic::CreateChoiceCards(player, m_source, ChoiceType::GENERAL,
                               m_choiceAction, result);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscoverTask::CloneImpl()
{
    return std::make_unique<DiscoverTask>(
        m_cards, m_discoverType, m_discoverCriteria.cardType,
        m_discoverCriteria.cardClass, m_discoverCriteria.race,
        m_discoverCriteria.rarity, m_choiceAction, m_numberOfChoices,
        m_doShuffle, m_keepAll);
}

std::vector<Card*> DiscoverTask::Discover(Game* game, Player* player,
                                          DiscoverType discoverType) const
{
    const FormatType format = game->GetFormatType();
    auto allCards = (format == FormatType::STANDARD)
                        ? Cards::GetAllStandardCards()
                        : Cards::GetAllWildCards();

    std::vector<Card*> cards;

    switch (discoverType)
    {
        case DiscoverType::SIX_COST_SUMMON:
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->GetCost() == 6)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        default:
            throw std::out_of_range(
                "DiscoverTask::Discover() - Invalid discover type");
    }

    return cards;
}

std::vector<Card*> DiscoverTask::Discover(Game* game, Player* player,
                                          DiscoverCriteria criteria) const
{
    const FormatType format = game->GetFormatType();
    std::vector<Card*> cards;

    if (criteria.cardClass == CardClass::INVALID ||
        criteria.cardClass == CardClass::PLAYER_CLASS ||
        criteria.cardClass == CardClass::ANOTHER_CLASS)
    {
        auto allCards = (format == FormatType::STANDARD)
                            ? Cards::GetAllStandardCards()
                            : Cards::GetAllWildCards();

        for (auto& card : allCards)
        {
            if (!criteria.Evaluate(card))
            {
                continue;
            }

            if (criteria.cardClass == CardClass::INVALID)
            {
                cards.emplace_back(card);
            }
            else if (criteria.cardClass == CardClass::PLAYER_CLASS)
            {
                if (card->GetCardClass() ==
                        player->GetHero()->card->GetCardClass() &&
                    card->GetCardClass() != CardClass::NEUTRAL)
                {
                    cards.emplace_back(card);
                }
            }
            else
            {
                if (card->GetCardClass() !=
                        player->GetHero()->card->GetCardClass() &&
                    card->GetCardClass() != CardClass::NEUTRAL)
                {
                    cards.emplace_back(card);
                }
            }
        }
    }
    else
    {
        auto allCards = (format == FormatType::STANDARD)
                            ? Cards::GetStandardCards(criteria.cardClass)
                            : Cards::GetWildCards(criteria.cardClass);

        for (auto& card : allCards)
        {
            if (!criteria.Evaluate(card))
            {
                continue;
            }

            if (card->GetCardClass() == criteria.cardClass)
            {
                cards.emplace_back(card);
            }
        }
    }

    return cards;
}
}  // namespace RosettaStone::SimpleTasks
