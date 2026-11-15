// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Games/Determinization.hpp>

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Triggers/MultiTrigger.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <algorithm>
#include <set>
#include <utility>

namespace RosettaStone::PlayMode
{
namespace
{
using Deck = std::array<Card*, START_DECK_SIZE>;
using KnownDraws = std::array<int, START_DECK_SIZE>;

std::array<const Player*, 2> Players(const Game& game)
{
    const auto* actor = game.GetCurrentPlayer();
    return { actor->playerType == PlayerType::PLAYER1 ? actor : actor->opponent,
             actor->playerType == PlayerType::PLAYER2 ? actor
                                                      : actor->opponent };
}

void CheckCard(Card* card)
{
    if (card->id.empty() || card->dbfID <= 0 ||
        Cards::FindCardByDbfID(card->dbfID) != card)
    {
        throw std::invalid_argument("Fixed decks require known card metadata");
    }

    const auto type = card->GetCardType();
    const auto* trigger = card->power.GetTrigger();

    if (!card->IsCollectible() ||
        (type != CardType::MINION && type != CardType::SPELL &&
         type != CardType::WEAPON) ||
        card->IsSecret() || card->IsQuest() ||
        card->HasGameTag(GameTag::SIDEQUEST) ||
        card->HasGameTag(GameTag::QUESTLINE) || !card->chooseCardIDs.empty() ||
        !card->power.GetTopdeckTask().empty() ||
        (trigger && (dynamic_cast<const MultiTrigger*>(trigger) ||
                     trigger->triggerActivation != TriggerActivation::PLAY)))
    {
        throw std::invalid_argument("Unsupported fixed-deck card");
    }
}

Deck SampleDeck(const Deck& deck, const KnownDraws& known,
                effolkronium::random_static::engine_type& random)
{
    std::vector<Card*> pool;

    for (auto* card : deck)
    {
        if (card)
        {
            CheckCard(card);
            pool.push_back(card);
        }
    }

    // Public deck lists are multisets; their supplied ordering is not evidence.
    std::ranges::sort(pool, {}, &Card::dbfID);

    const auto size = pool.size();
    Deck sampled{};

    for (std::size_t i = 0; i < known.size(); ++i)
    {
        if (known[i] == 0)
        {
            continue;
        }

        const auto found = std::ranges::find(pool, known[i], &Card::dbfID);

        if (known[i] < 0 || i >= size || found == pool.end())
        {
            throw std::invalid_argument("Known draws exceed the fixed deck");
        }

        sampled[i] = *found;
        pool.erase(found);
    }

    std::ranges::shuffle(pool, random);

    auto next = pool.begin();

    for (std::size_t i = 0; i < size; ++i)
    {
        if (!sampled[i])
        {
            sampled[i] = *next++;
        }
    }

    return sampled;
}

struct DeckHistory
{
    std::vector<int> entities;
    std::set<int> known;
    int coinID = -1;
    std::size_t remaining = 0;
};

DeckHistory TrackDeck(const Player& player, const Deck& deck,
                      const KnownDraws& known)
{
    DeckHistory history;

    for (const auto* card : player.GetHandZone()->GetAll())
    {
        const int id = card->GetGameTag(GameTag::ENTITY_ID);

        if (card->card->id == "GAME_005")
        {
            history.coinID = id;
            history.known.insert(id);
        }
        else
        {
            history.entities.push_back(id);
        }
    }

    const auto remaining = player.GetDeckZone()->GetAll();

    for (auto it = remaining.rbegin(); it != remaining.rend(); ++it)
    {
        history.entities.push_back((*it)->GetGameTag(GameTag::ENTITY_ID));
    }

    history.remaining = remaining.size();

    if (std::cmp_not_equal(history.entities.size(),
                           std::ranges::count_if(deck, [](auto* card) {
                               return card != nullptr;
                           })))
    {
        throw std::invalid_argument("Unsupported initial draw effects");
    }

    for (std::size_t i = 0; i < history.entities.size(); ++i)
    {
        if (const auto* entity =
                player.game->entityList.at(history.entities[i]);
            entity->card != deck[i])
        {
            throw std::invalid_argument("Initial draw order has changed");
        }

        if (known[i] != 0)
        {
            history.known.insert(history.entities[i]);
        }
    }

    return history;
}

void CheckKnown(const DeckHistory& history, int entityID)
{
    if (!history.known.contains(entityID))
    {
        throw std::invalid_argument("Missing a previously revealed draw");
    }
}

void CheckZones(const Player& player, const Deck& deck, DeckHistory& history,
                bool ownHand)
{
    if (player.choice || !player.GetSecretZone()->IsEmpty())
    {
        throw std::invalid_argument(
            "Hidden choices and secrets are unsupported");
    }

    const auto remaining = player.GetDeckZone()->GetAll();

    if (remaining.size() > history.remaining)
    {
        throw std::invalid_argument("Cards added to a deck are unsupported");
    }

    const auto drawn = history.entities.size() - remaining.size();

    for (std::size_t i = 0; i < remaining.size(); ++i)
    {
        const auto* card = remaining[remaining.size() - i - 1];

        if (card->GetGameTag(GameTag::ENTITY_ID) !=
                history.entities[drawn + i] ||
            card->card != deck[drawn + i])
        {
            throw std::invalid_argument(
                "Deck order or identities have changed");
        }
    }

    history.remaining = remaining.size();

    for (const auto* card : player.GetHandZone()->GetAll())
    {
        const int id = card->GetGameTag(GameTag::ENTITY_ID);
        if (const auto found = std::ranges::find(history.entities, id);
            (id == history.coinID && card->card->id != "GAME_005") ||
            (id != history.coinID &&
             (found == history.entities.end() ||
              card->card != deck[found - history.entities.begin()])))
        {
            throw std::invalid_argument(
                "Generated or transformed hands are unsupported");
        }

        if (ownHand)
        {
            CheckKnown(history, id);
        }
    }

    // Burns and other public exits also reveal a card, even without a play.
    for (const int id : history.entities)
    {
        const auto found = player.game->entityList.find(id);
        if (found == player.game->entityList.end() ||
            (found->second->GetZoneType() != ZoneType::DECK &&
             found->second->GetZoneType() != ZoneType::HAND))
        {
            CheckKnown(history, id);
        }
    }
}
}  // namespace

PublicAction EncodePublicAction(const Game& game, std::size_t actionIndex)
{
    if (actionIndex >= PolicySchema::NUM_ACTIONS)
    {
        throw std::invalid_argument("Invalid public action index");
    }

    PublicAction action{ actionIndex, EncodePublicObservation(game), {} };
    const auto players = Players(game);

    for (std::size_t i = 0; i < players.size(); ++i)
    {
        for (const auto* card : players[i]->GetGraveyardZone()->GetAll())
        {
            if (card->card->IsSecret())
            {
                throw std::invalid_argument(
                    "Secret graveyards are unsupported");
            }

            action.graveyardsAfter[i].push_back(card->card->dbfID);
        }
    }

    return action;
}

std::unique_ptr<ReplayGame> SampleDeterminization(
    const FixedDeckInformationSet& information,
    effolkronium::random_static::engine_type& random)
{
    const auto concreteSeat = [](PlayerType seat) {
        return seat == PlayerType::PLAYER1 || seat == PlayerType::PLAYER2;
    };

    if (&random == &effolkronium::random_static::engine() ||
        !concreteSeat(information.actingPlayer) ||
        !concreteSeat(information.config.startPlayer) ||
        information.config.doFillDecks || !information.config.skipMulligan)
    {
        throw std::invalid_argument("Invalid fixed-deck information set setup");
    }

    auto nextRandom = random;
    auto config = information.config;

    config.doShuffle = false;
    config.player1Deck =
        SampleDeck(config.player1Deck, information.knownDraws[0], nextRandom);
    config.player2Deck =
        SampleDeck(config.player2Deck, information.knownDraws[1], nextRandom);

    const auto seed = static_cast<unsigned int>(nextRandom());
    const ReplayGame initial(config, seed);
    const effolkronium::random_static::engine_type initialRandom(seed);

    const auto players = Players(initial.GetGame());
    const std::array decks{ config.player1Deck, config.player2Deck };
    std::array initialHistories{
        TrackDeck(*players[0], decks[0], information.knownDraws[0]),
        TrackDeck(*players[1], decks[1], information.knownDraws[1])
    };

    const auto check = [&](const ReplayGame& game, auto& tracked,
                           bool isFinal) {
        const auto currentPlayers = Players(game.GetGame());

        for (std::size_t i = 0; i < currentPlayers.size(); ++i)
        {
            CheckZones(*currentPlayers[i], decks[i], tracked[i],
                       isFinal && currentPlayers[i]->playerType ==
                                      information.actingPlayer);
        }
    };

    if (initial.GetRandomState() != initialRandom)
    {
        throw std::invalid_argument("Random startup effects are unsupported");
    }

    check(initial, initialHistories, false);

    for (std::size_t replayAttempt = 0; replayAttempt < 256; ++replayAttempt)
    {
        auto sampled = initial.Branch();
        auto histories = initialHistories;
        bool randomHistory = false;

        try
        {
            bool matched = true;

            for (const auto& entry : information.history)
            {
                const PolicyActions policy(sampled->GetGame());
                const auto action = policy.Decode(entry.actionIndex);

                if (action.type == PlayerActionType::CHOOSE)
                {
                    throw std::invalid_argument(
                        "Choice history is unsupported");
                }

                if (action.type == PlayerActionType::PLAY_CARD)
                {
                    const auto owner =
                        sampled->GetCurrentPlayer()->playerType ==
                                PlayerType::PLAYER1
                            ? 0
                            : 1;
                    CheckKnown(histories[owner], action.sourceID);
                }

                matched = false;

                for (std::size_t attempt = 0; attempt < 256; ++attempt)
                {
                    auto candidate = sampled->Branch();
                    const auto outcomeSeed =
                        static_cast<unsigned int>(nextRandom());

                    candidate->ApplyAction(action, outcomeSeed);

                    const bool randomOutcome = candidate->GetRandomState() !=
                                               Random::engine_type(outcomeSeed);
                    auto tracked = histories;

                    try
                    {
                        check(*candidate, tracked, false);
                    }
                    catch (const std::invalid_argument&)
                    {
                        if (!randomOutcome)
                        {
                            throw;
                        }

                        continue;
                    }

                    const bool samePublicState =
                        candidate->GetOutcome(information.actingPlayer) ==
                            PlayState::PLAYING &&
                        EncodePublicAction(candidate->GetGame(),
                                           entry.actionIndex) == entry;

                    if (!samePublicState)
                    {
                        if (!randomOutcome)
                        {
                            throw std::invalid_argument(
                                "Sample disagrees with public history");
                        }

                        continue;
                    }

                    sampled = std::move(candidate);
                    histories = std::move(tracked);
                    randomHistory |= randomOutcome;
                    matched = true;

                    break;
                }

                if (!matched)
                {
                    break;
                }
            }

            if (!matched)
            {
                if (!randomHistory)
                {
                    throw std::runtime_error(
                        "Public outcome sampling budget exhausted");
                }

                continue;
            }

            check(*sampled, histories, true);

            if (sampled->GetCurrentPlayer()->playerType !=
                    information.actingPlayer ||
                EncodeObservation(sampled->GetGame()) !=
                    information.observation)
            {
                throw std::invalid_argument(
                    "Sample disagrees with the observation");
            }

            random = nextRandom;
            return sampled;
        }
        catch (const std::invalid_argument&)
        {
            if (!randomHistory)
            {
                throw;
            }

            // A later play or private observation can reject an earlier
            // outcome.
        }
    }

    throw std::runtime_error("Information set sampling budget exhausted");
}
}  // namespace RosettaStone::PlayMode
