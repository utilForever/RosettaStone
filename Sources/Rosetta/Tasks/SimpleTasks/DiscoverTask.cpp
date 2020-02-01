// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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
        Card* pick = nullptr;

        for (std::size_t i = 0; i < numberOfChoices; ++i)
        {
            while (true)
            {
                pick = cardsToDiscover[Random::get<std::size_t>(
                    0, cardsToDiscover.size() - 1)];

                if (std::find(result.begin(), result.end(), pick) ==
                    result.end())
                {
                    break;
                }
            }

            result[i] = pick;
        }
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

    auto result = GetChoices(cardsToDiscover, m_numberOfChoices);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscoverTask::CloneImpl()
{
    return std::make_unique<DiscoverTask>(m_discoverCriteria.cardType,
                                          m_discoverCriteria.cardClass);
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
