// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Determinization.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <algorithm>
#include <set>

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
        std::reverse(opponentDeck.begin(), opponentDeck.end());

        ReplayGame second(alternate, 900);

        std::ranges::reverse(alternate.player1Deck);
        std::ranges::reverse(alternate.player2Deck);

        const auto equivalent = Opening(second, alternate);

        REQUIRE(information.observation == equivalent.observation);
        REQUIRE(information.knownDraws == equivalent.knownDraws);
        REQUIRE(HiddenCards(*first.GetCurrentPlayer()->opponent) !=
                HiddenCards(*second.GetCurrentPlayer()->opponent));

        const auto ambient = Random::engine();
        std::set<std::vector<int>> opponentSamples, deckSamples;

        for (unsigned int seed = 0; seed < 16; ++seed)
        {
            Random::engine_type left(seed), right(seed);

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
            opponentSamples.insert(HiddenCards(*actor->opponent));

            for (const auto& action : EnumerateActions(sample->GetGame()))
            {
                const auto branch = sample->Branch();
                CHECK_NOTHROW(branch->ApplyAction(action));
            }

            CHECK(EncodeObservation(sample->GetGame()) ==
                  information.observation);
        }

        CHECK_GT(deckSamples.size(), 1);
        CHECK_GT(opponentSamples.size(), 1);
        CHECK(EncodeObservation(first.GetGame()) == information.observation);
    }
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
