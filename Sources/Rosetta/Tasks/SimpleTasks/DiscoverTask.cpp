// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscoverTask.hpp>

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
                           Rarity rarity, ChoiceAction choiceAction)
    : m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction)
{
    // Do nothing
}

DiscoverTask::DiscoverTask(const std::vector<std::string>& cardIDs,
                           ChoiceAction choiceAction, int numberOfChoices)
    : m_choiceAction(choiceAction), m_numberOfChoices(numberOfChoices)
{
    for (auto& cardID : cardIDs)
    {
        m_cards.emplace_back(Cards::FindCardByID(cardID));
    }
}

DiscoverTask::DiscoverTask(std::vector<Card*> cards, CardType cardType,
                           CardClass cardClass, Race race, Rarity rarity,
                           ChoiceAction choiceAction, int numberOfChoices)
    : m_cards(std::move(cards)),
      m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction),
      m_numberOfChoices(numberOfChoices)
{
    // Do nothing
}

std::vector<Card*> DiscoverTask::GetChoices(std::vector<Card*> cardsToDiscover,
                                            std::size_t numberOfChoices)
{
    std::vector<Card*> result;

    if (numberOfChoices >= cardsToDiscover.size())
    {
        result = cardsToDiscover;
    }
    else
    {
        result.reserve(numberOfChoices);
        std::sample(cardsToDiscover.begin(), cardsToDiscover.end(),
                    std::back_inserter(result), numberOfChoices,
                    Random::get_engine());
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
    else
    {
        const auto cardsToDiscover =
            Discover(player->game->GetFormatType(), m_discoverCriteria);
        result = GetChoices(cardsToDiscover, m_numberOfChoices);
    }

    Generic::CreateChoiceCards(player, m_source, ChoiceType::GENERAL,
                               m_choiceAction, result);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscoverTask::CloneImpl()
{
    return std::make_unique<DiscoverTask>(
        m_cards, m_discoverCriteria.cardType, m_discoverCriteria.cardClass,
        m_discoverCriteria.race, m_discoverCriteria.rarity, m_choiceAction,
        m_numberOfChoices);
}

std::vector<Card*> DiscoverTask::Discover(FormatType format,
                                          DiscoverCriteria criteria)
{
    std::vector<Card*> cards;

    if (criteria.cardClass == CardClass::INVALID ||
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
            else
            {
                if (card->GetCardClass() !=
                        m_player->GetHero()->card->GetCardClass() &&
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
