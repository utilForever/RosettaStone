// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscoverTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
DiscoverCriteria::DiscoverCriteria(CardType _cardType, CardClass _cardClass)
    : cardType(_cardType), cardClass(_cardClass)
{
    // Do nothing
}

bool DiscoverCriteria::Evaluate(Card* card) const
{
    return cardType == CardType::INVALID || card->GetCardType() == cardType;
}

DiscoverTask::DiscoverTask(CardType cardType, CardClass cardClass,
                           ChoiceAction ChoiceAction)
    : m_discoverCriteria(cardType, cardClass), m_choiceAction(ChoiceAction)
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
    std::vector<Card*> cardsToDiscover;

    if (m_discoverType != DiscoverType::INVALID)
    {
        // TODO: Add code later
    }
    else
    {
        cardsToDiscover =
            Discover(player->game->GetFormatType(), m_discoverCriteria);
    }

    const auto result = GetChoices(cardsToDiscover, m_numberOfChoices);

    Generic::CreateChoiceCards(player, m_source, ChoiceType::GENERAL,
                               m_choiceAction, result);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscoverTask::CloneImpl()
{
    return std::make_unique<DiscoverTask>(m_discoverCriteria.cardType,
                                          m_discoverCriteria.cardClass,
                                          m_choiceAction);
}

std::vector<Card*> DiscoverTask::Discover(FormatType format,
                                          DiscoverCriteria criteria)
{
    std::vector<Card*> cards;

    if (criteria.cardClass == CardClass::INVALID)
    {
        // TODO: Add code later
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
