// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Determinization.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <algorithm>
#include <set>
#include <string_view>

using namespace RosettaStone;
using namespace PlayMode;
using Random = effolkronium::random_static;

namespace
{
GameConfig FixedConfig()
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.doShuffle = false;

    const std::array ids{
        "CS2_231", "EX1_049", "EX1_015", "CS2_023", "CS2_172",
        "CS2_120", "CS1_042", "EX1_008", "CS2_182", "CS2_119",
        "CS2_200", "CS2_186", "CS2_171", "CS2_189", "LOEA10_3"
    };

    for (std::size_t i = 0; i < config.player1Deck.size(); ++i)
    {
        config.player1Deck[i] = Cards::FindCardByID(ids[i % ids.size()]);
    }

    config.player2Deck = config.player1Deck;

    return config;
}

FixedDeckInformationSet Opening(const ReplayGame& replay,
                                const GameConfig& publicConfig)
{
    FixedDeckInformationSet information;
    information.config = publicConfig;
    information.actingPlayer = replay.GetCurrentPlayer()->playerType;
    information.observation = EncodeObservation(replay.GetGame());

    const auto owner = information.actingPlayer == PlayerType::PLAYER1 ? 0 : 1;

    // Only the observer's four visible opening draws enter the information set.
    for (std::size_t i = 0; i < 4; ++i)
    {
        information.knownDraws[owner][i] =
            information.observation.hand[i][ObservationSchema::CARD_ID];
    }

    return information;
}

void Record(FixedDeckInformationSet& information, ReplayGame& replay,
            const PlayerAction& action = {})
{
    const auto index = PolicyActions(replay.GetGame()).Encode(action);

    replay.ApplyAction(action);
    information.history.emplace_back(index,
                                     EncodePublicObservation(replay.GetGame()));
}

PlayerAction Play(const ReplayGame& replay, std::string_view cardID,
                  int targetID = -1)
{
    for (const auto& action : EnumerateActions(replay.GetGame()))
    {
        if (action.type == PlayerActionType::PLAY_CARD &&
            action.targetID == targetID &&
            replay.GetGame().entityList.at(action.sourceID)->card->id == cardID)
        {
            return action;
        }
    }

    throw std::logic_error("Missing test card play");
}

std::vector<int> HiddenCards(const Player& player)
{
    std::vector<int> cards;

    for (const auto* card : player.GetHandZone()->GetAll())
    {
        cards.push_back(card->card->dbfID);
    }

    cards.push_back(-1);

    for (const auto* card : player.GetDeckZone()->GetAll())
    {
        cards.push_back(card->card->dbfID);
    }

    return cards;
}

void CheckDeckMultiset(const Player& player, const GameConfig& config)
{
    auto actual = HiddenCards(player);

    std::erase(actual, -1);
    std::erase(actual, Cards::FindCardByID("GAME_005")->dbfID);
    std::ranges::sort(actual);

    std::vector<int> expected;

    for (const auto* card : config.player1Deck)
    {
        if (card)
        {
            expected.push_back(card->dbfID);
        }
    }

    std::ranges::sort(expected);

    CHECK(actual == expected);
}
}  // namespace

TEST_CASE(
    "[Determinization] - EquivalentInformationSetsAndIndependentRandomState")
{
    for (const auto starter : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
    {
        auto config = FixedConfig();
        config.startPlayer = starter;

        ReplayGame first(config, 100);
        auto information = Opening(first, config);

        auto alternate = config;
        auto& actorDeck = starter == PlayerType::PLAYER1
                              ? alternate.player1Deck
                              : alternate.player2Deck;
        auto& opponentDeck = starter == PlayerType::PLAYER1
                                 ? alternate.player2Deck
                                 : alternate.player1Deck;

        std::reverse(actorDeck.begin() + 4, actorDeck.end());
        std::ranges::reverse(opponentDeck);

        ReplayGame second(alternate, 900);

        std::ranges::reverse(alternate.player1Deck);
        std::ranges::reverse(alternate.player2Deck);

        const auto equivalent = Opening(second, alternate);

        REQUIRE(information.observation == equivalent.observation);
        REQUIRE(information.knownDraws == equivalent.knownDraws);
        REQUIRE(HiddenCards(*first.GetCurrentPlayer()->opponent) !=
                HiddenCards(*second.GetCurrentPlayer()->opponent));

        const auto ambient = Random::engine();
        std::set<std::vector<int>> opponentHands;
        std::set<std::vector<int>> opponentDecks;
        std::set<std::vector<int>> deckSamples;

        for (unsigned int seed = 0; seed < 16; ++seed)
        {
            Random::engine_type left(seed);
            Random::engine_type right(seed);

            const auto sample = SampleDeterminization(information, left);
            const auto repeated = SampleDeterminization(equivalent, right);

            CHECK(left == right);
            CHECK(left != Random::engine_type(seed));
            CHECK(Random::engine() == ambient);
            CHECK(sample->GetRandomState() == repeated->GetRandomState());
            CHECK(EncodeObservation(sample->GetGame()) ==
                  information.observation);
            CHECK(PolicyActions(sample->GetGame()).GetLegalMask() ==
                  PolicyActions(first.GetGame()).GetLegalMask());

            const auto* actor = sample->GetCurrentPlayer();

            CHECK(HiddenCards(*actor) ==
                  HiddenCards(*repeated->GetCurrentPlayer()));
            CHECK(HiddenCards(*actor->opponent) ==
                  HiddenCards(*repeated->GetCurrentPlayer()->opponent));
            CheckDeckMultiset(*actor, config);
            CheckDeckMultiset(*actor->opponent, config);

            deckSamples.insert(HiddenCards(*actor));

            const auto hidden = HiddenCards(*actor->opponent);
            const auto separator = std::ranges::find(hidden, -1);
            std::vector<int> hand(hidden.begin(), separator);

            std::ranges::sort(hand);

            opponentHands.insert(hand);
            opponentDecks.emplace(separator + 1, hidden.end());

            for (const auto& action : EnumerateActions(sample->GetGame()))
            {
                const auto branch = sample->Branch();
                CHECK_NOTHROW(branch->ApplyAction(action));
            }

            CHECK(EncodeObservation(sample->GetGame()) ==
                  information.observation);
        }

        CHECK_GT(deckSamples.size(), 1);
        CHECK_GT(opponentHands.size(), 1);
        CHECK_GT(opponentDecks.size(), 1);
        CHECK(EncodeObservation(first.GetGame()) == information.observation);
    }
}

TEST_CASE("[Determinization] - PublicHistoryDrawsGraveyardAndRevealedBounce")
{
    auto config = FixedConfig();
    ReplayGame real(config, 1069);
    auto information = Opening(real, config);

    Record(information, real, Play(real, "CS2_231"));
    Record(information, real);
    Record(information, real, Play(real, "CS2_231"));
    Record(information, real);
    Record(information, real, Play(real, "EX1_015"));
    Record(information, real);

    const auto* opponentWisp =
        real.GetCurrentPlayer()->GetFieldZone()->GetAll()[0];

    Record(information, real,
           Play(real, "EX1_049", opponentWisp->GetGameTag(GameTag::ENTITY_ID)));
    Record(information, real);

    const auto* actor = real.GetCurrentPlayer();
    const auto* wisp = actor->GetFieldZone()->GetAll()[1];
    const auto* brewmaster = actor->opponent->GetFieldZone()->GetAll()[0];

    Record(information, real,
           { PlayerActionType::ATTACK, wisp->GetGameTag(GameTag::ENTITY_ID),
             brewmaster->GetGameTag(GameTag::ENTITY_ID) });

    // The observer saw its next three draws and the opponent's two plays.
    for (std::size_t i = 4; i < 7; ++i)
    {
        information.knownDraws[0][i] = config.player1Deck[i]->dbfID;
    }

    information.knownDraws[1][0] = Cards::FindCardByID("CS2_231")->dbfID;
    information.knownDraws[1][1] = Cards::FindCardByID("EX1_049")->dbfID;
    information.observation = EncodeObservation(real.GetGame());

    const auto ambient = Random::engine();

    for (unsigned int seed = 0; seed < 12; ++seed)
    {
        Random::engine_type random(seed);

        const auto sample = SampleDeterminization(information, random);
        const auto* player = sample->GetCurrentPlayer();

        CHECK(EncodeObservation(sample->GetGame()) == information.observation);
        CHECK_EQ(player->GetGraveyardZone()->GetCount(), 1);
        CHECK_EQ(player->GetGraveyardZone()->GetAll()[0]->card->id, "CS2_231");
        CHECK_EQ(player->opponent->GetHandZone()->GetAll().back()->card->id,
                 "CS2_231");
        CHECK_EQ(player->opponent->GetFieldZone()->GetMinions()[0]->GetHealth(),
                 1);
        CHECK(PolicyActions(sample->GetGame()).GetLegalMask() ==
              PolicyActions(real.GetGame()).GetLegalMask());

        const auto branch = sample->Branch();

        CHECK(EncodeObservation(branch->GetGame()) == information.observation);
        CHECK(HiddenCards(*branch->GetCurrentPlayer()->opponent) ==
              HiddenCards(*player->opponent));
        CHECK(branch->GetRandomState() == sample->GetRandomState());
    }

    CHECK(Random::engine() == ambient);

    information.knownDraws[1][0] = 0;

    Random::engine_type random(5);

    CHECK_THROWS_AS(SampleDeterminization(information, random),
                    std::invalid_argument);
    CHECK(random == Random::engine_type(5));
}

TEST_CASE("[Determinization] - KnownFutureDrawAndEmptyDecks")
{
    auto config = FixedConfig();

    SUBCASE("KnownNextCard")
    {
        ReplayGame real(config, 7);
        auto information = Opening(real, config);
        const auto nextCard = config.player1Deck[4]->dbfID;

        information.knownDraws[0][4] = nextCard;

        for (unsigned int seed = 0; seed < 8; ++seed)
        {
            Random::engine_type random(seed);

            const auto sample = SampleDeterminization(information, random);

            CHECK_EQ(sample->GetCurrentPlayer()
                         ->GetDeckZone()
                         ->GetTopCard()
                         ->card->dbfID,
                     nextCard);

            sample->ApplyAction({});
            sample->ApplyAction({});

            CHECK_EQ(sample->GetCurrentPlayer()
                         ->GetHandZone()
                         ->GetAll()
                         .back()
                         ->card->dbfID,
                     nextCard);
        }
    }
    SUBCASE("NoUnknownAlternatives")
    {
        config.player1Deck.fill(nullptr);
        config.player2Deck.fill(nullptr);

        ReplayGame real(config, 8);

        FixedDeckInformationSet information;
        information.config = config;
        information.actingPlayer = PlayerType::PLAYER1;
        information.observation = EncodeObservation(real.GetGame());

        Random::engine_type random(0);

        const auto sample = SampleDeterminization(information, random);

        CHECK(EncodeObservation(sample->GetGame()) == information.observation);
        CHECK(sample->GetCurrentPlayer()->GetHandZone()->IsEmpty());
        CHECK(sample->GetCurrentPlayer()->opponent->GetDeckZone()->IsEmpty());
        CHECK_EQ(sample->GetCurrentPlayer()
                     ->opponent->GetHandZone()
                     ->GetAll()[0]
                     ->card->id,
                 "GAME_005");
    }
}

TEST_CASE("[Determinization] - PublicBurnsAndFatigue")
{
    auto config = FixedConfig();
    bool fatigue = false;

    SUBCASE("Burns")
    {
        // Do nothing special for burns, just use the default configuration
    }
    SUBCASE("Fatigue")
    {
        fatigue = true;
        std::fill(config.player1Deck.begin() + 5, config.player1Deck.end(),
                  nullptr);
        config.player2Deck = config.player1Deck;
    }

    ReplayGame real(config, 17);
    auto information = Opening(real, config);
    const int turns = fatigue ? 4 : 14;

    for (int i = 0; i < turns; ++i)
    {
        Record(information, real);
    }

    for (std::size_t i = 4; i < (fatigue ? 5U : 11U); ++i)
    {
        information.knownDraws[0][i] = config.player1Deck[i]->dbfID;
    }

    if (!fatigue)
    {
        information.knownDraws[1][9] = config.player2Deck[9]->dbfID;
        information.knownDraws[1][10] = config.player2Deck[10]->dbfID;
    }

    information.observation = EncodeObservation(real.GetGame());

    Random::engine_type random(19);
    const auto sample = SampleDeterminization(information, random);

    CHECK(EncodeObservation(sample->GetGame()) == information.observation);
    CHECK_EQ(sample->GetCurrentPlayer()->GetHero()->fatigue, fatigue ? 1 : 0);
    CHECK_EQ(sample->GetCurrentPlayer()->GetGraveyardZone()->GetCount(),
             fatigue ? 0 : 1);
    CHECK_EQ(
        sample->GetCurrentPlayer()->opponent->GetGraveyardZone()->GetCount(),
        fatigue ? 0 : 2);

    if (!fatigue)
    {
        const auto before = random;
        const auto ambient = Random::engine();

        information.knownDraws[1][9] = 0;

        CHECK_THROWS_WITH_AS(SampleDeterminization(information, random),
                             "Missing a previously revealed draw",
                             std::invalid_argument);
        CHECK(random == before);
        CHECK(Random::engine() == ambient);
    }
}

TEST_CASE("[Determinization] - InvalidKnowledgeIsAtomic")
{
    auto config = FixedConfig();
    ReplayGame real(config, 5);
    auto information = Opening(real, config);

    SUBCASE("InvalidObserver")
    {
        information.actingPlayer = PlayerType::RANDOM;
    }
    SUBCASE("UnknownStarter")
    {
        information.config.startPlayer = PlayerType::RANDOM;
    }
    SUBCASE("Mulligan")
    {
        information.config.skipMulligan = false;
    }
    SUBCASE("DeckFilling")
    {
        information.config.doFillDecks = true;
    }
    SUBCASE("UnknownCard")
    {
        information.knownDraws[0][0] = -1;
    }
    SUBCASE("UnknownCardMetadata")
    {
        information.config.player2Deck[0] = Cards::FindCardByID("missing-card");
    }
    SUBCASE("KnownDrawPastEnd")
    {
        information.config.player2Deck.back() = nullptr;
        information.knownDraws[1].back() = config.player2Deck.back()->dbfID;
    }
    SUBCASE("TooManyCopies")
    {
        information.knownDraws[0].fill(Cards::FindCardByID("CS2_231")->dbfID);
    }
    SUBCASE("MissingPrivateDraw")
    {
        // Fix the other draws to avoid an unrelated observation mismatch.
        for (std::size_t i = 1; i < config.player1Deck.size(); ++i)
        {
            information.knownDraws[0][i] = config.player1Deck[i]->dbfID;
        }

        information.knownDraws[0][0] = 0;
    }
    SUBCASE("WrongObservation")
    {
        ++information.observation.heroes[0][ObservationSchema::HEALTH];
    }
    SUBCASE("IllegalAction")
    {
        information.history.push_back({ PolicySchema::NUM_ACTIONS, {} });
    }
    SUBCASE("WrongPublicCheckpoint")
    {
        Record(information, real, Play(real, "CS2_231"));

        information.observation = EncodeObservation(real.GetGame());
        ++information.history[0]
              .publicAfter.turn[ObservationSchema::TURN_NUMBER];
    }
    SUBCASE("PrivateDataInPublicCheckpoint")
    {
        Record(information, real, Play(real, "CS2_231"));

        information.observation = EncodeObservation(real.GetGame());
        information.history[0].publicAfter = EncodeObservation(real.GetGame());
    }
    SUBCASE("SecretDeck")
    {
        information.config.player2Deck[0] = Cards::FindCardByID("EX1_287");
    }
    SUBCASE("RandomHistory")
    {
        config.player1Deck[0] = Cards::FindCardByID("EX1_277");

        ReplayGame randomGame(config, 9);

        information = Opening(randomGame, config);

        // A lone enemy hero need not consume RNG on every standard library.
        Record(information, randomGame);
        Record(information, randomGame, Play(randomGame, "CS2_231"));

        information.knownDraws[1][0] = config.player2Deck[0]->dbfID;

        Record(information, randomGame);

        information.knownDraws[0][4] = config.player1Deck[4]->dbfID;

        const auto before = randomGame.GetRandomState();

        Record(information, randomGame, Play(randomGame, "EX1_277"));

        REQUIRE(randomGame.GetRandomState() != before);

        information.observation = EncodeObservation(randomGame.GetGame());
    }

    Random::engine_type random(12);
    const auto ambient = Random::engine();

    CHECK_THROWS_AS(SampleDeterminization(information, random),
                    std::invalid_argument);
    CHECK(random == Random::engine_type(12));
    CHECK(Random::engine() == ambient);
}

TEST_CASE("[Determinization] - RandomDiscardCannotRewritePublicHistory")
{
    auto config = FixedConfig();
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARLOCK;

    const std::array ids{
        "EX1_308", "CS2_182", "CS2_120", "CS2_172", "CS1_042",
        "CS2_231", "EX1_049", "EX1_015", "EX1_008", "CS2_119",
        "CS2_200", "CS2_186", "CS2_171", "CS2_189", "LOEA10_3"
    };

    for (std::size_t i = 0; i < config.player1Deck.size(); ++i)
    {
        config.player1Deck[i] = Cards::FindCardByID(ids[i % ids.size()]);
    }

    config.player2Deck = config.player1Deck;

    ReplayGame real(config, 0);
    auto information = Opening(real, config);

    Record(information, real);

    const auto* opponent = real.GetCurrentPlayer();

    Record(information, real,
           Play(real, "EX1_308",
                opponent->opponent->GetHero()->GetGameTag(GameTag::ENTITY_ID)));
    REQUIRE_EQ(opponent->GetGraveyardZone()->GetCount(), 2);

    // Record the public play and discard without assuming a library's shuffle
    // order.
    for (const auto* card : opponent->GetGraveyardZone()->GetAll())
    {
        const auto found = std::ranges::find(config.player2Deck, card->card);

        if (found != config.player2Deck.end())
        {
            information.knownDraws[1][found - config.player2Deck.begin()] =
                card->card->dbfID;
        }
    }

    Record(information, real);

    information.observation = EncodeObservation(real.GetGame());
    information.knownDraws[0][4] =
        information.observation.hand[4][ObservationSchema::CARD_ID];

    const auto ambient = Random::engine();

    for (unsigned int seed = 0; seed < 8; ++seed)
    {
        CAPTURE(seed);

        Random::engine_type random(seed);

        CHECK_THROWS_WITH_AS(SampleDeterminization(information, random),
                             "Random history is unsupported",
                             std::invalid_argument);
        CHECK(random == Random::engine_type(seed));
        CHECK(Random::engine() == ambient);
    }

    CHECK(EncodeObservation(real.GetGame()) == information.observation);
}

TEST_CASE("[Determinization] - AmbientRandomCannotBeShared")
{
    const auto config = FixedConfig();
    ReplayGame real(config, 10);
    const auto information = Opening(real, config);
    const auto ambient = Random::engine();

    CHECK_THROWS_AS(SampleDeterminization(information, Random::engine()),
                    std::invalid_argument);
    CHECK(Random::engine() == ambient);

    Random::engine_type left(11);
    Random::engine_type right(11);

    const auto first = SampleDeterminization(information, left);

    Random::seed(444);

    const auto changedAmbient = Random::engine();
    const auto second = SampleDeterminization(information, right);

    CHECK(Random::engine() == changedAmbient);

    Random::engine() = ambient;

    CHECK(HiddenCards(*first->GetCurrentPlayer()->opponent) ==
          HiddenCards(*second->GetCurrentPlayer()->opponent));
    CHECK(first->GetRandomState() == second->GetRandomState());
    CHECK(left == right);
}

TEST_CASE("[Determinization] - PublicEncoderNeverReadsHandsOrDecks")
{
    ReplayGame real(FixedConfig(), 9);
    const auto expected = EncodePublicObservation(real.GetGame());

    CHECK(expected.hand == Observation{}.hand);
    CHECK(expected.chooseOne == Observation{}.chooseOne);
    CHECK_EQ(expected.players[0][ObservationSchema::HAND_COUNT], 4);
    CHECK_EQ(expected.players[1][ObservationSchema::HAND_COUNT], 5);

    std::vector<std::pair<Playable*, Card*>> hidden;
    const auto* actor = real.GetCurrentPlayer();

    for (const auto* player :
         { actor, static_cast<const Player*>(actor->opponent) })
    {
        for (auto* card : player->GetHandZone()->GetAll())
        {
            hidden.emplace_back(card, card->card);
            card->card = nullptr;
        }

        for (auto* card : player->GetDeckZone()->GetAll())
        {
            hidden.emplace_back(card, card->card);
            card->card = nullptr;
        }
    }

    CHECK(EncodePublicObservation(real.GetGame()) == expected);

    for (const auto& [entity, card] : hidden)
    {
        entity->card = card;
    }
}
