// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscoverTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

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

bool DiscoverCriteria::Evaluate(const Card* card) const
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
                           int repeat, bool doShuffle)
    : m_discoverType(discoverType),
      m_numberOfChoices(numberOfChoices),
      m_repeat(repeat),
      m_doShuffle(doShuffle)
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

std::vector<int> DiscoverTask::GetChoices(const Entity* source,
                                          std::vector<Card*> cardsForGeneration,
                                          std::vector<int> cardsForOtherEffect,
                                          int numberOfChoices, bool doShuffle)
{
    std::vector<int> result;

    if (!cardsForGeneration.empty())
    {
        std::vector<Card*> selectedCards;

        if (numberOfChoices >= static_cast<int>(cardsForGeneration.size()))
        {
            selectedCards = cardsForGeneration;
        }
        else
        {
            selectedCards.reserve(numberOfChoices);

            if (doShuffle)
            {
                Random::shuffle(cardsForGeneration);
            }

            for (int i = 0; i < numberOfChoices; ++i)
            {
                selectedCards.emplace_back(cardsForGeneration[i]);
            }
        }

        for (const auto& card : selectedCards)
        {
            std::map<GameTag, int> cardTags;
            cardTags.emplace(GameTag::CREATOR,
                             source->GetGameTag(GameTag::ENTITY_ID));
            cardTags.emplace(GameTag::DISPLAYED_CREATOR,
                             source->GetGameTag(GameTag::ENTITY_ID));

            Playable* choiceEntity =
                Entity::GetFromCard(source->player, card, cardTags,
                                    source->player->GetSetasideZone());
            source->player->GetSetasideZone()->Add(choiceEntity);
            result.emplace_back(choiceEntity->GetGameTag(GameTag::ENTITY_ID));
        }
    }
    else if (!cardsForOtherEffect.empty())
    {
        if (numberOfChoices >= static_cast<int>(cardsForOtherEffect.size()))
        {
            result = cardsForOtherEffect;
        }
        else
        {
            result.reserve(numberOfChoices);

            if (doShuffle)
            {
                Random::shuffle(cardsForOtherEffect);
            }

            for (int i = 0; i < numberOfChoices; ++i)
            {
                result.emplace_back(cardsForOtherEffect[i]);
            }
        }
    }

    return result;
}

TaskStatus DiscoverTask::Impl(Player* player)
{
    std::vector<int> result;
    std::vector<Card*> cardsForGeneration;
    std::vector<int> cardsForOtherEffect;

    if (!m_cards.empty())
    {
        result = GetChoices(m_source, m_cards, std::vector<int>{},
                            m_numberOfChoices, m_doShuffle);
    }
    else if (m_discoverType != DiscoverType::INVALID)
    {
        std::tie(cardsForGeneration, cardsForOtherEffect) =
            Discover(player->game, player, m_discoverType, m_choiceAction);
        result = GetChoices(m_source, cardsForGeneration, cardsForOtherEffect,
                            m_numberOfChoices, m_doShuffle);
    }
    else
    {
        cardsForGeneration = Discover(player->game, player, m_discoverCriteria);
        result = GetChoices(m_source, cardsForGeneration, cardsForOtherEffect,
                            m_numberOfChoices, m_doShuffle);
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
            Playable* playable = player->game->entityList[result[i]];
            player->GetSetasideZone()->Remove(playable);
            Generic::AddCardToHand(player, playable);
        }
    }

    Generic::CreateChoice(player, m_source, ChoiceType::GENERAL, m_choiceAction,
                          result);

    if (m_repeat > 1)
    {
        Choice* currentChoice = player->choice;

        for (int i = 1; i < m_repeat; ++i)
        {
            const auto choice = new Choice(player, cardsForGeneration);
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

auto DiscoverTask::Discover(const Game* game, Player* player,
                            DiscoverType discoverType,
                            ChoiceAction& choiceAction) const
    -> std::tuple<std::vector<Card*>, std::vector<int>>
{
    std::vector<Card*> allCards =
        Cards::GetDiscoverCards(player->baseClass, game->GetFormatType());

    std::vector<Card*> cardsForGeneration;
    std::vector<int> cardsForOtherEffect;
    choiceAction = ChoiceAction::INVALID;

    switch (discoverType)
    {
        case DiscoverType::INVALID:
            throw std::invalid_argument(
                "DiscoverTask::Discover() - Invalid discover type");
        case DiscoverType::DECK:
        {
            choiceAction = ChoiceAction::DRAW_FROM_DECK;
            for (const auto& playable : player->GetDeckZone()->GetAll())
            {
                cardsForOtherEffect.emplace_back(
                    playable->GetGameTag(GameTag::ENTITY_ID));
            }
            break;
        }
        case DiscoverType::HERO_POWER:
        {
            choiceAction = ChoiceAction::CHANGE_HERO_POWER;
            cardsForGeneration = {
                Cards::FindCardByID("HERO_01bp"),
                Cards::FindCardByID("HERO_02bp"),
                Cards::FindCardByID("HERO_03bp"),
                Cards::FindCardByID("HERO_04bp"),
                Cards::FindCardByID("HERO_05bp"),
                Cards::FindCardByID("HERO_06bp"),
                Cards::FindCardByID("HERO_07bp"),
                Cards::FindCardByID("HERO_08bp"),
                Cards::FindCardByID("HERO_09bp"),
                Cards::FindCardByID("HERO_10bp"),
            };
            break;
        }
        case DiscoverType::ENEMY_DECK:
        {
            choiceAction = ChoiceAction::HAND_COPY;
            for (const auto& playable :
                 player->opponent->GetDeckZone()->GetAll())
            {
                cardsForOtherEffect.emplace_back(
                    playable->GetGameTag(GameTag::ENTITY_ID));
            }
            break;
        }
        case DiscoverType::SPELL_FROM_DECK:
        {
            choiceAction = ChoiceAction::DRAW_FROM_DECK;
            for (const auto& playable : player->GetDeckZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::SPELL)
                {
                    cardsForOtherEffect.emplace_back(
                        playable->GetGameTag(GameTag::ENTITY_ID));
                }
            }
            break;
        }
        case DiscoverType::BASIC_TOTEM:
            choiceAction = ChoiceAction::SUMMON;
            cardsForGeneration = { Cards::FindCardByID("AT_132_SHAMANa"),
                                   Cards::FindCardByID("AT_132_SHAMANb"),
                                   Cards::FindCardByID("AT_132_SHAMANc"),
                                   Cards::FindCardByID("AT_132_SHAMANe") };
            break;
        case DiscoverType::BASIC_TOTEM_CLASSIC:
            choiceAction = ChoiceAction::SUMMON;
            cardsForGeneration = { Cards::FindCardByID("AT_132_SHAMANa"),
                                   Cards::FindCardByID("AT_132_SHAMANb"),
                                   Cards::FindCardByID("AT_132_SHAMANc"),
                                   Cards::FindCardByID("AT_132_SHAMANd") };
            break;
        case DiscoverType::CHOOSE_ONE:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->HasGameTag(GameTag::CHOOSE_ONE))
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::ONE_COST_CARD:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCost() == 1)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::THREE_COST_CARD:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCost() == 3)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::FOUR_COST_CARD:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCost() == 4)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SIX_COST_MINION_SUMMON:
            choiceAction = ChoiceAction::SUMMON;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->GetCost() == 6)
                {
                    cardsForGeneration.emplace_back(card);
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
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::TAUNT_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::TAUNT) == 1)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DEATHRATTLE_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::DEATHRATTLE) == 1)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::RUSH_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::RUSH) == 1)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SPELLPOWER_MINION:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::MINION &&
                    card->HasGameTag(GameTag::SPELLPOWER) == 1)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DEATHRATTLE_MINION_DIED:
            choiceAction = ChoiceAction::HAND_AND_STACK;
            for (const auto& playable : player->GetGraveyardZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::MINION &&
                    playable->HasDeathrattle() && playable->isDestroyed)
                {
                    cardsForGeneration.emplace_back(playable->card);
                }
            }
            break;
        case DiscoverType::SPELL:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SPELL_AND_STACK:
            choiceAction = ChoiceAction::HAND_AND_STACK;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::HOLY_SPELL:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL &&
                    card->GetSpellSchool() == SpellSchool::HOLY)
                {
                    cardsForGeneration.emplace_back(card);
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
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SECRET:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->IsSecret())
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::BEAST:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetRace() == Race::BEAST)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DEMON:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetRace() == Race::DEMON)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::DRAGON:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetRace() == Race::DRAGON)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::MECHANICAL:
            choiceAction = ChoiceAction::HAND;
            for (auto& card : allCards)
            {
                if (card->GetRace() == Race::MECHANICAL)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::LACKEY:
            choiceAction = ChoiceAction::HAND;
            for (const auto& card : Cards::GetAllCards())
            {
                if (card->IsLackey())
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::HEISTBARON_TOGWAGGLE:
            choiceAction = ChoiceAction::HAND;
            cardsForGeneration = { Cards::FindCardByID("LOOT_998h"),
                                   Cards::FindCardByID("LOOT_998j"),
                                   Cards::FindCardByID("LOOT_998l"),
                                   Cards::FindCardByID("LOOT_998k") };
            break;
        case DiscoverType::MADAME_LAZUL:
            choiceAction = ChoiceAction::MADAME_LAZUL;
            for (const auto& playable :
                 player->opponent->GetHandZone()->GetAll())
            {
                cardsForOtherEffect.emplace_back(
                    playable->GetGameTag(GameTag::ENTITY_ID));
            }
            break;
        case DiscoverType::SWAMPQUEEN_HAGATHA:
            choiceAction = ChoiceAction::SWAMPQUEEN_HAGATHA;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL &&
                    card->GetCardClass() == CardClass::SHAMAN)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::TORTOLLAN_PILGRIM:
        {
            choiceAction = ChoiceAction::TORTOLLAN_PILGRIM;
            for (const auto& playable : player->GetDeckZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::SPELL)
                {
                    cardsForOtherEffect.emplace_back(
                        playable->GetGameTag(GameTag::ENTITY_ID));
                }
            }
            break;
        }
        case DiscoverType::FROM_STACK:
        {
            choiceAction = ChoiceAction::STACK;
            for (const auto& playable : game->taskStack.playables)
            {
                cardsForGeneration.emplace_back(playable->card);
            }
            break;
        }
        case DiscoverType::SIAMAT:
            choiceAction = ChoiceAction::SIAMAT;
            cardsForGeneration = { Cards::FindCardByID("ULD_178a2"),
                                   Cards::FindCardByID("ULD_178a"),
                                   Cards::FindCardByID("ULD_178a3"),
                                   Cards::FindCardByID("ULD_178a4") };
            break;
        case DiscoverType::SIR_FINLEY_OF_THE_SANDS:
            choiceAction = ChoiceAction::CHANGE_HERO_POWER;
            cardsForGeneration = {
                Cards::FindCardByID("HERO_01bp2"),
                Cards::FindCardByID("HERO_02bp2"),
                Cards::FindCardByID("HERO_03bp2"),
                Cards::FindCardByID("HERO_04bp2"),
                Cards::FindCardByID("HERO_05bp2"),
                Cards::FindCardByID("HERO_06bp2"),
                Cards::FindCardByID("HERO_07bp2"),
                Cards::FindCardByID("HERO_08bp2"),
                Cards::FindCardByID("HERO_09bp2"),
                Cards::FindCardByID("HERO_10bp2"),
            };
            break;
        case DiscoverType::VULPERA_SCOUNDREL:
            choiceAction = ChoiceAction::VULPERA_SCOUNDREL;
            for (auto& card : allCards)
            {
                if (card->GetCardType() == CardType::SPELL)
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            Random::shuffle(cardsForGeneration.begin(),
                            cardsForGeneration.end());
            cardsForGeneration.resize(3);
            cardsForGeneration.emplace_back(Cards::FindCardByID("ULD_209t"));
            break;
        case DiscoverType::BODY_WRAPPER:
            choiceAction = ChoiceAction::DECK;
            for (const auto& playable : player->GetGraveyardZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::MINION &&
                    playable->isDestroyed)
                {
                    cardsForGeneration.emplace_back(playable->card);
                }
            }
            break;
        case DiscoverType::RINLINGS_RIFLE:
            choiceAction = ChoiceAction::CAST_SPELL;
            for (auto& card : allCards)
            {
                if (card->IsSecret())
                {
                    cardsForGeneration.emplace_back(card);
                }
            }
            break;
        case DiscoverType::SELECTIVE_BREEDER:
            choiceAction = ChoiceAction::HAND_COPY;
            for (const auto& playable : player->GetDeckZone()->GetAll())
            {
                if (playable->card->GetCardType() == CardType::MINION &&
                    playable->card->GetRace() == Race::BEAST)
                {
                    cardsForOtherEffect.emplace_back(
                        playable->GetGameTag(GameTag::ENTITY_ID));
                }
            }
            break;
        case DiscoverType::ARCH_THIEF_RAFAAM:
            choiceAction = ChoiceAction::HAND;
            cardsForGeneration = {
                Cards::FindCardByID("LOEA16_3"),
                Cards::FindCardByID("LOEA16_5"),
                Cards::FindCardByID("LOEA16_4"),
            };
            break;
    }

    if (!cardsForOtherEffect.empty())
    {
        std::sort(cardsForOtherEffect.begin(), cardsForOtherEffect.end(),
                  [&player](const int& a, const int& b) {
                      const Playable* playableA = player->game->entityList[a];
                      const Playable* playableB = player->game->entityList[b];

                      return playableA->card->dbfID < playableB->card->dbfID;
                  });

        const auto last = std::unique(
            cardsForOtherEffect.begin(), cardsForOtherEffect.end(),
            [&player](const int& a, const int& b) {
                const Playable* playableA = player->game->entityList[a];
                const Playable* playableB = player->game->entityList[b];

                return playableA->card->dbfID == playableB->card->dbfID;
            });

        cardsForOtherEffect.erase(last, cardsForOtherEffect.end());
        Random::shuffle(cardsForOtherEffect.begin(), cardsForOtherEffect.end());
    }

    return std::make_tuple(cardsForGeneration, cardsForOtherEffect);
}

std::vector<Card*> DiscoverTask::Discover(const Game* game,
                                          const Player* player,
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
