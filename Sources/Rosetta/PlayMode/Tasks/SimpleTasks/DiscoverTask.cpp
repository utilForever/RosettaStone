// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscoverTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

#include <utility>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
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
                           Rarity rarity, ChoiceAction choiceAction, int repeat,
                           bool keepAll)
    : m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction),
      m_repeat(repeat),
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

DiscoverTask::DiscoverTask(DiscoverType discoverType, int numberOfChoices,
                           int repeat)
    : m_discoverType(discoverType),
      m_numberOfChoices(numberOfChoices),
      m_repeat(repeat)
{
    // Do nothing
}

DiscoverTask::DiscoverTask(std::vector<Card*> cards, DiscoverType discoverType,
                           CardType cardType, CardClass cardClass, Race race,
                           Rarity rarity, ChoiceAction choiceAction,
                           int numberOfChoices, bool doShuffle, int repeat,
                           bool keepAll)
    : m_cards(std::move(cards)),
      m_discoverType(discoverType),
      m_discoverCriteria(cardType, cardClass, race, rarity),
      m_choiceAction(choiceAction),
      m_numberOfChoices(numberOfChoices),
      m_repeat(repeat),
      m_doShuffle(doShuffle),
      m_keepAll(keepAll)
{
    // Do nothing
}

std::vector<Card*> DiscoverTask::GetChoices(std::vector<Card*> cardsToDiscover,
                                            int numberOfChoices, bool doShuffle)
{
    std::vector<Card*> result;

    if (numberOfChoices >= static_cast<int>(cardsToDiscover.size()))
    {
        result = cardsToDiscover;
    }
    else
    {
        result.reserve(numberOfChoices);

        if (doShuffle)
        {
            std::sample(cardsToDiscover.begin(), cardsToDiscover.end(),
                        std::back_inserter(result), numberOfChoices,
                        Random::get_engine());
        }
        else
        {
            for (int i = 0; i < numberOfChoices; ++i)
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
    std::vector<Card*> cardsToDiscover;

    if (!m_cards.empty())
    {
        result = GetChoices(m_cards, m_numberOfChoices);
    }
    else if (m_discoverType != DiscoverType::INVALID)
    {
        cardsToDiscover =
            Discover(player->game, player, m_discoverType, m_choiceAction);
        result = GetChoices(cardsToDiscover, m_numberOfChoices);
    }
    else
    {
        cardsToDiscover = Discover(player->game, player, m_discoverCriteria);
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

    if (m_repeat > 1)
    {
        Choice* currentChoice = player->choice;

        for (int i = 1; i < m_repeat; ++i)
        {
            auto choice = new Choice(player, cardsToDiscover);
            choice->choiceType = ChoiceType::GENERAL;
            choice->choiceAction = m_choiceAction;
            choice->source = m_source;
            choice->depth = i + 1;

            currentChoice->nextChoice = choice;
            currentChoice = choice;
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscoverTask::CloneImpl()
{
    return std::make_unique<DiscoverTask>(
        m_cards, m_discoverType, m_discoverCriteria.cardType,
        m_discoverCriteria.cardClass, m_discoverCriteria.race,
        m_discoverCriteria.rarity, m_choiceAction, m_numberOfChoices,
        m_doShuffle, m_repeat, m_keepAll);
}

std::vector<Card*> DiscoverTask::Discover(Game* game, Player* player,
                                          DiscoverType discoverType,
                                          ChoiceAction& choiceAction) const
{
    const FormatType format = game->GetFormatType();

    // NOTE: Assume there is no card that has 'CardType::SPELL' and 'CardClass::NEUTRAL'.
    std::vector<Card*> allCards;
    if (format == FormatType::STANDARD)
    {
        for (const auto& card : Cards::GetAllStandardCards())
        {
            if ((card->IsCardClass(player->baseClass) && !card->IsQuest()) ||
                (card->GetCardType() != CardType::SPELL &&
                 card->GetCardClass() == CardClass::NEUTRAL))
            {
                allCards.emplace_back(card);
            }
        }
    }
    else
    {
        for (const auto& card : Cards::GetAllWildCards())
        {
            if ((card->IsCardClass(player->baseClass) && !card->IsQuest()) ||
                (card->GetCardType() != CardType::SPELL &&
                 card->GetCardClass() == CardClass::NEUTRAL))
            {
                allCards.emplace_back(card);
            }
        }
    }

    std::vector<Card*> cards;
    choiceAction = ChoiceAction::INVALID;

    switch (discoverType)
    {
        case DiscoverType::SPELL:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::CHOOSE_ONE:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->HasGameTag(GameTag::CHOOSE_ONE))
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DRAGON:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetRace() == Race::DRAGON)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::LEGENDARY_MINION_SUMMON:
            choiceAction = ChoiceAction::SUMMON;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->GetRarity() == Rarity::LEGENDARY)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DEATHRATTLE_MINION_DIED:
            choiceAction = ChoiceAction::HAND_AND_STACK;
            for (auto& playable : player->GetGraveyardZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::MINION &&
                    playable->HasDeathrattle() && playable->isDestroyed)
                {
                    cards.emplace_back(playable->card);
                }
            }
            break;
        case DiscoverType::SIX_COST_SUMMON:
            choiceAction = ChoiceAction::SUMMON;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->GetCost() == 6)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SPELL_THREE_COST_OR_LESS:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL &&
                    card->GetCost() <= 3)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::HEISTBARON_TOGWAGGLE:
            choiceAction = ChoiceAction::HAND;
            cards = { Cards::FindCardByID("LOOT_998h"),
                      Cards::FindCardByID("LOOT_998j"),
                      Cards::FindCardByID("LOOT_998l"),
                      Cards::FindCardByID("LOOT_998k") };
            break;
        case DiscoverType::MADAME_LAZUL:
            choiceAction = ChoiceAction::HAND;
            for (auto& playable : player->opponent->GetHandZone()->GetAll())
            {
                cards.emplace_back(playable->card);
            }
            break;
        case DiscoverType::SWAMPQUEEN_HAGATHA:
            choiceAction = ChoiceAction::SWAMPQUEEN_HAGATHA;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL &&
                    card->GetCardClass() == CardClass::SHAMAN)
                {
                    cards.emplace_back(card);
                }
            }
            break;
        case DiscoverType::TORTOLLAN_PILGRIM:
        {
            choiceAction = ChoiceAction::TORTOLLAN_PILGRIM;

            std::vector<int> list;
            for (auto& playable : player->GetDeckZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::SPELL)
                {
                    list.emplace_back(playable->card->dbfID);
                }
            }

            std::sort(list.begin(), list.end());
            const auto last = std::unique(list.begin(), list.end());
            list.erase(last, list.end());
            Random::shuffle(list.begin(), list.end());

            for (auto& dbfID : list)
            {
                cards.emplace_back(Cards::FindCardByDbfID(dbfID));
            }

            break;
        }
        case DiscoverType::FOUR_COST_ONE:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCost() == 4)
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
}  // namespace RosettaStone::PlayMode::SimpleTasks
