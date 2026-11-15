// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Agents/InformationSetSearch.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CustomTask.hpp>

#include <algorithm>
#include <limits>
#include <set>
#include <string_view>

using namespace RosettaStone;
using namespace PlayMode;

namespace
{
GameConfig MirrorConfig(PlayerType starter)
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.startPlayer = starter;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.doShuffle = false;

    const std::array ids{ "EX1_277", "CS2_231", "CS2_182", "CS2_200",
                          "CS2_186" };

    for (std::size_t i = 0; i < config.player1Deck.size(); ++i)
    {
        config.player1Deck[i] = Cards::FindCardByID(ids[i % ids.size()]);
    }

    config.player2Deck = config.player1Deck;

    return config;
}

PlayerAction Play(const ReplayGame& game, std::string_view cardID)
{
    for (const auto& action : EnumerateActions(game.GetGame()))
    {
        if (action.type == PlayerActionType::PLAY_CARD &&
            game.GetGame().entityList.at(action.sourceID)->card->id == cardID)
        {
            return action;
        }
    }

    throw std::logic_error("Missing fixture card play");
}

void Record(FixedDeckInformationSet& information, ReplayGame& game,
            const PlayerAction& action = {})
{
    const auto index = PolicyActions(game.GetGame()).Encode(action);

    game.ApplyAction(action);
    information.history.push_back(EncodePublicAction(game.GetGame(), index));
}

FixedDeckInformationSet Opening(const GameConfig& config,
                                const ReplayGame& game)
{
    FixedDeckInformationSet information;
    information.config = config;
    information.actingPlayer = config.startPlayer;
    information.observation = EncodeObservation(game.GetGame());

    const auto seat = config.startPlayer == PlayerType::PLAYER1 ? 0 : 1;

    for (std::size_t i = 0; i < 4; ++i)
    {
        information.knownDraws[seat][i] =
            information.observation.hand[i][ObservationSchema::CARD_ID];
    }

    return information;
}

void CheckSame(const InformationSetSearchResult& left,
               const InformationSetSearchResult& right)
{
    CHECK_EQ(left.visitCount, right.visitCount);
    CHECK(left.GetRootAction() == right.GetRootAction());
    REQUIRE_EQ(left.actions.size(), right.actions.size());

    for (std::size_t i = 0; i < left.actions.size(); ++i)
    {
        CHECK_EQ(left.actions[i].actionIndex, right.actions[i].actionIndex);
        CHECK_EQ(left.actions[i].player, right.actions[i].player);
        CHECK_EQ(left.actions[i].prior, right.actions[i].prior);
        CHECK_EQ(left.actions[i].visitCount, right.actions[i].visitCount);
        CHECK_EQ(left.actions[i].totalValue, right.actions[i].totalValue);
    }
}

class RecordingEvaluator final : public BatchedEvaluator
{
 public:
    std::vector<Observation> observations;
    std::vector<PolicySchema::LegalMask> masks;
    std::optional<std::size_t> onlyAction;
    float value = 0.0f;

 private:
    std::vector<EvaluationResult> EvaluateBatch(
        std::span<const EvaluationInput> inputs) override
    {
        for (const auto& input : inputs)
        {
            observations.push_back(input.observation);
            masks.push_back(input.legalMask);
        }

        UniformEvaluator uniform;
        auto results = uniform.Evaluate(inputs);

        for (auto& result : results)
        {
            result.value = value;

            if (onlyAction && result.priors[*onlyAction] > 0.0f)
            {
                std::ranges::fill(result.priors, 0.0f);
                result.priors[*onlyAction] = 1.0f;
            }
        }

        return results;
    }
};
}  // namespace

TEST_CASE("[InformationSetSearch] - ReproducibleHiddenAndRandomMirrorDecisions")
{
    for (const auto starter : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
    {
        const auto config = MirrorConfig(starter);
        ReplayGame real(config, 42);
        auto information = Opening(config, real);
        const auto own = starter == PlayerType::PLAYER1 ? 0 : 1;

        Record(information, real);
        Record(information, real, Play(real, "CS2_231"));
        Record(information, real);

        information.knownDraws[1 - own][1] =
            Cards::FindCardByID("CS2_231")->dbfID;
        information.observation = EncodeObservation(real.GetGame());
        information.knownDraws[own][4] =
            information.observation.hand[4][ObservationSchema::CARD_ID];

        const auto ambient = Random::engine();
        const auto realRandom = real.GetRandomState();
        const PolicyActions rootPolicy(real.GetGame());
        RecordingEvaluator first;
        const auto result =
            SearchInformationSet(information, first, { 256, 3 }, 1070);

        REQUIRE(result.GetRootAction());
        CHECK_EQ(rootPolicy.GetLegalMask()[*result.GetRootAction()], 1);
        CHECK_EQ(result.visitCount, 256);

        std::size_t visits = 0;

        for (const auto& action : result.actions)
        {
            CHECK_EQ(rootPolicy.GetLegalMask()[action.actionIndex], 1);
            visits += action.visitCount;
        }

        CHECK_EQ(visits, 255);
        CHECK(Random::engine() == ambient);
        CHECK(real.GetRandomState() == realRandom);
        CHECK(EncodeObservation(real.GetGame()) == information.observation);

        // Equivalent public multisets must not leak supplied deck ordering.
        std::ranges::reverse(information.config.player1Deck);
        std::ranges::reverse(information.config.player2Deck);

        Random::discard(31);

        const auto changedAmbient = Random::engine();
        RecordingEvaluator repeated;
        const auto again =
            SearchInformationSet(information, repeated, { 256, 3 }, 1070);

        CheckSame(result, again);
        CHECK(first.observations == repeated.observations);
        CHECK(first.masks == repeated.masks);
        CHECK(Random::engine() == changedAmbient);

        Random::engine() = ambient;

        RecordingEvaluator different;
        SearchInformationSet(information, different, { 256, 3 }, 1071);

        CHECK(first.observations != different.observations);

        std::set<
            std::array<ObservationSchema::Card, ObservationSchema::HAND_SLOTS>>
            hands;
        std::set<int> missileHealth;
        std::set<PolicySchema::LegalMask> missileMasks;

        for (std::size_t i = 0; i < first.observations.size(); ++i)
        {
            const auto& observation = first.observations[i];

            if (observation.turn[ObservationSchema::TURN_NUMBER] == 4)
            {
                hands.insert(observation.hand);
            }

            if (observation.turn[ObservationSchema::TURN_NUMBER] == 3 &&
                observation.heroes[1][ObservationSchema::HEALTH] < 30 &&
                observation.hand[0][ObservationSchema::CARD_ID] !=
                    Cards::FindCardByID("EX1_277")->dbfID)
            {
                missileHealth.insert(
                    observation.heroes[1][ObservationSchema::HEALTH]);
                missileMasks.insert(first.masks[i]);
            }
        }

        CHECK_GT(hands.size(), 1);
        CHECK_GT(missileHealth.size(), 1);
        CHECK_GT(missileMasks.size(), 1);
        CHECK_NOTHROW(
            real.ApplyAction(rootPolicy.Decode(*result.GetRootAction())));
    }
}
