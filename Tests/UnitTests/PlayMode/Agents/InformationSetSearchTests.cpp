// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Agents/InformationSetSearch.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CustomTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/EnqueueTask.hpp>

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

TEST_CASE("[InformationSetSearch] - RandomTerminalBranchesAreResampled")
{
    for (const auto starter : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
    {
        auto config = MirrorConfig(starter);
        config.player1Deck.fill(nullptr);

        const std::array ids{ "EX1_277", "CS2_182", "CS2_029", "CS2_186" };

        for (std::size_t i = 0; i < ids.size(); ++i)
        {
            config.player1Deck[i] = Cards::FindCardByID(ids[i]);
        }

        config.player2Deck = config.player1Deck;

        ReplayGame real(config, 0);
        auto information = Opening(config, real);
        const auto own = starter == PlayerType::PLAYER1 ? 0 : 1;

        for (int turn = 0; turn < 14; ++turn)
        {
            Record(information, real);

            if (turn == 6)
            {
                Record(information, real, Play(real, "CS2_182"));
                information.knownDraws[1 - own][1] =
                    Cards::FindCardByID("CS2_182")->dbfID;
            }
        }

        information.observation = EncodeObservation(real.GetGame());

        REQUIRE_EQ(information.observation.heroes[0][ObservationSchema::HEALTH],
                   2);
        REQUIRE_EQ(information.observation.heroes[1][ObservationSchema::HEALTH],
                   2);

        const PolicyActions policy(real.GetGame());
        const auto missiles = policy.Encode(Play(real, "EX1_277"));
        UniformEvaluator evaluator;

        const auto ambient = Random::engine();

        const auto result =
            SearchInformationSet(information, evaluator, { 256, 1 }, 1070, 8.0);
        const auto repeated =
            SearchInformationSet(information, evaluator, { 256, 1 }, 1070, 8.0);

        CheckSame(result, repeated);
        CHECK(Random::engine() == ambient);
        REQUIRE(result.GetRootAction());
        CHECK_EQ(*result.GetRootAction(), PolicySchema::END_TURN);

        const auto randomAction =
            std::ranges::find(result.actions, missiles, &PUCTNode::actionIndex);

        REQUIRE(randomAction != result.actions.end());
        CHECK_GT(randomAction->totalValue, 0.0);
        CHECK_LT(randomAction->totalValue,
                 static_cast<double>(randomAction->visitCount));

        const auto endTurn = std::ranges::find(
            result.actions, PolicySchema::END_TURN, &PUCTNode::actionIndex);

        REQUIRE(endTurn != result.actions.end());
        CHECK_GT(endTurn->visitCount, 1);
        CHECK_EQ(endTurn->GetMeanValue(), 1.0);

        const auto self =
            real.GetCurrentPlayer()->GetHero()->GetGameTag(GameTag::ENTITY_ID);
        const auto selfFireball =
            std::ranges::find_if(result.actions, [&](const auto& statistics) {
                const auto action = policy.Decode(statistics.actionIndex);
                return action.type == PlayerActionType::PLAY_CARD &&
                       action.targetID == self;
            });

        REQUIRE(selfFireball != result.actions.end());
        CHECK_GT(selfFireball->visitCount, 0);
        CHECK_EQ(selfFireball->GetMeanValue(), -1.0);

        real.ApplyAction(policy.Decode(*result.GetRootAction()));

        CHECK_EQ(real.GetReward(starter), 1);
    }
}

TEST_CASE("[InformationSetSearch] - SimulationRandomStreamsAreIndependent")
{
    const auto config = MirrorConfig(PlayerType::PLAYER1);
    ReplayGame real(config, 0);
    auto information = Opening(config, real);

    Record(information, real);
    Record(information, real, Play(real, "CS2_231"));
    Record(information, real);

    information.knownDraws[1][1] = Cards::FindCardByID("CS2_231")->dbfID;
    information.observation = EncodeObservation(real.GetGame());
    information.knownDraws[0][4] =
        information.observation.hand[4][ObservationSchema::CARD_ID];

    // Instrument the real search path. Consume extra RNG only after the first
    // simulation's visible outcome, with no further actions at depth one.
    auto& tasks = Cards::FindCardByID("EX1_277")->power.GetPowerTask();

    struct RestoreTasks
    {
        std::vector<std::shared_ptr<ITask>>& tasks;
        std::vector<std::shared_ptr<ITask>> saved;

        ~RestoreTasks()
        {
            tasks = std::move(saved);
        }
    } restore{ tasks, tasks };

    std::vector<Random::engine_type> starts;
    bool consumeExtra = false;

    tasks.insert(tasks.begin(), std::make_shared<SimpleTasks::CustomTask>(
                                    [&starts](Player*, Entity*, Playable*) {
                                        starts.push_back(Random::engine());
                                    }));
    const auto consumeRandom = std::make_shared<SimpleTasks::CustomTask>(
        [&starts, &consumeExtra](Player*, Entity*, Playable*) {
            if (starts.size() == 1)
            {
                CHECK(Random::engine() != starts.front());

                if (consumeExtra)
                {
                    Random::discard(1000);
                }
            }
        });

    // Arcane Missiles enqueues its damage, so queue this probe behind it.
    tasks.push_back(std::make_shared<SimpleTasks::EnqueueTask>(
        TaskList{ consumeRandom }, 1));

    const auto missiles =
        PolicyActions(real.GetGame()).Encode(Play(real, "EX1_277"));
    const auto ambient = Random::engine();

    RecordingEvaluator first;
    first.onlyAction = missiles;

    const auto result =
        SearchInformationSet(information, first, { 32, 1 }, 1070);
    const auto originalStarts = starts;

    REQUIRE_EQ(originalStarts.size(), 31);

    starts.clear();
    consumeExtra = true;

    RecordingEvaluator repeated;
    repeated.onlyAction = missiles;

    const auto again =
        SearchInformationSet(information, repeated, { 32, 1 }, 1070);

    REQUIRE_EQ(starts.size(), originalStarts.size());
    CHECK(starts.front() == originalStarts.front());

    const bool sameStreams = starts == originalStarts;

    CHECK(sameStreams);
    CheckSame(result, again);
    CHECK(first.observations == repeated.observations);
    CHECK(first.masks == repeated.masks);
    CHECK(Random::engine() == ambient);
}

TEST_CASE("[InformationSetSearch] - SearchContinuesAfterRandomActions")
{
    for (const auto starter : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
    {
        auto config = MirrorConfig(starter);
        config.player1Deck[2] = Cards::FindCardByID("EX1_277");
        config.player2Deck = config.player1Deck;

        ReplayGame real(config, 42);
        auto information = Opening(config, real);
        const auto own = starter == PlayerType::PLAYER1 ? 0 : 1;

        Record(information, real);
        Record(information, real, Play(real, "CS2_231"));
        Record(information, real);

        information.knownDraws[1 - own][1] =
            Cards::FindCardByID("CS2_231")->dbfID;
        information.knownDraws[own][4] = config.player1Deck[4]->dbfID;

        for (int cast = 0; cast < 2; ++cast)
        {
            const auto before = real.GetRandomState();

            Record(information, real, Play(real, "EX1_277"));

            if (cast == 0)
            {
                REQUIRE(real.GetRandomState() != before);
            }

            information.observation = EncodeObservation(real.GetGame());

            const auto ambient = Random::engine();
            const auto realRandom = real.GetRandomState();
            UniformEvaluator evaluator;

            const auto result =
                SearchInformationSet(information, evaluator, { 32, 2 }, 1070);
            const auto again =
                SearchInformationSet(information, evaluator, { 32, 2 }, 1070);

            CheckSame(result, again);
            REQUIRE(result.GetRootAction());
            CHECK_EQ(PolicyActions(real.GetGame())
                         .GetLegalMask()[*result.GetRootAction()],
                     1);
            CHECK(EncodeObservation(real.GetGame()) == information.observation);
            CHECK(real.GetRandomState() == realRandom);
            CHECK(Random::engine() == ambient);
        }
    }
}

TEST_CASE("[InformationSetSearch] - SearchContinuesAfterPrivateRandomActions")
{
    for (const auto starter : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
    {
        auto config = MirrorConfig(starter);
        config.player1Class = CardClass::WARRIOR;
        config.player2Class = CardClass::WARRIOR;
        config.player1Deck.fill(nullptr);

        const std::array ids{ "DMF_531", "CS2_231", "CS2_182", "CS2_200" };

        for (std::size_t i = 0; i < ids.size(); ++i)
        {
            config.player1Deck[i] = Cards::FindCardByID(ids[i]);
        }

        config.player2Deck = config.player1Deck;

        std::unique_ptr<ReplayGame> real;
        FixedDeckInformationSet information;

        // Choose a real outcome that buffs Wisp, without assuming a library's
        // random distribution mapping. Only the observed result enters search.
        for (unsigned int seed = 0; seed < 64; ++seed)
        {
            real = std::make_unique<ReplayGame>(config, seed);
            information = Opening(config, *real);

            Record(information, *real);
            Record(information, *real);
            Record(information, *real, Play(*real, "DMF_531"));

            information.observation = EncodeObservation(real->GetGame());

            if (information.observation.hand[0][ObservationSchema::ATTACK] == 2)
            {
                break;
            }
        }

        REQUIRE_EQ(information.observation.hand[0][ObservationSchema::ATTACK],
                   2);

        for (int phase = 0; phase < 3; ++phase)
        {
            CAPTURE(starter);
            CAPTURE(phase);

            if (phase == 1)
            {
                Record(information, *real, Play(*real, "CS2_231"));
            }
            else if (phase == 2)
            {
                Record(information, *real);
                Record(information, *real);
            }

            information.observation = EncodeObservation(real->GetGame());

            const auto ambient = Random::engine();
            const auto realRandom = real->GetRandomState();
            UniformEvaluator evaluator;

            const auto result =
                SearchInformationSet(information, evaluator, { 16, 1 }, 1070);
            const auto repeated =
                SearchInformationSet(information, evaluator, { 16, 1 }, 1070);

            CheckSame(result, repeated);
            REQUIRE(result.GetRootAction());
            CHECK_EQ(PolicyActions(real->GetGame())
                         .GetLegalMask()[*result.GetRootAction()],
                     1);
            CHECK(EncodeObservation(real->GetGame()) ==
                  information.observation);
            CHECK(real->GetRandomState() == realRandom);
            CHECK(Random::engine() == ambient);
        }

        // Impossible private evidence must fail without advancing either RNG.
        information.observation.hand[0][ObservationSchema::ATTACK] += 100;

        Random::engine_type random(12);

        const auto ambient = Random::engine();

        CHECK_THROWS_WITH_AS(SampleDeterminization(information, random),
                             "Information set sampling budget exhausted",
                             std::runtime_error);
        CHECK(random == Random::engine_type(12));
        CHECK(Random::engine() == ambient);
    }
}

TEST_CASE("[InformationSetSearch] - PrivateHistoriesStayWithTheirObserver")
{
    auto config = MirrorConfig(PlayerType::PLAYER1);
    config.player1Deck.fill(Cards::FindCardByID("CS2_231"));
    config.player1Deck[0] = Cards::FindCardByID("EX1_277");
    config.player2Deck = config.player1Deck;

    ReplayGame real(config, 0);

    auto information = Opening(config, real);
    information.knownDraws[0][4] = Cards::FindCardByID("CS2_231")->dbfID;

    RecordingEvaluator evaluator;
    evaluator.onlyAction = PolicySchema::END_TURN;

    SearchInformationSet(information, evaluator, { 64, 2 }, 1070);

    std::size_t ownNextDecisions = 0;
    std::set<std::array<ObservationSchema::Card, ObservationSchema::HAND_SLOTS>>
        opponentHands;

    for (const auto& observation : evaluator.observations)
    {
        if (observation.turn[ObservationSchema::TURN_NUMBER] == 2)
        {
            opponentHands.insert(observation.hand);
        }
        else if (observation.turn[ObservationSchema::TURN_NUMBER] == 3)
        {
            ++ownNextDecisions;
        }
    }

    CHECK_GT(opponentHands.size(), 1);
    // Opponent hand samples must not split an identical own decision.
    CHECK_EQ(ownNextDecisions, 1);
}

TEST_CASE("[InformationSetSearch] - PublicDiscardsStayInHistory")
{
    auto config = MirrorConfig(PlayerType::PLAYER1);
    config.player1Deck.fill(Cards::FindCardByID("CS2_231"));
    config.player2Class = CardClass::WARLOCK;
    config.player2Deck.fill(nullptr);

    const std::array ids{ "EX1_308", "CS2_182", "CS2_200", "CS2_186" };

    for (std::size_t i = 0; i < ids.size(); ++i)
    {
        config.player2Deck[i] = Cards::FindCardByID(ids[i]);
    }

    ReplayGame real(config, 0);
    auto information = Opening(config, real);

    // Fully known draw slots isolate the public discard from hidden sampling.
    for (std::size_t i = 0; i < ids.size(); ++i)
    {
        information.knownDraws[1][i] = config.player2Deck[i]->dbfID;
    }

    auto opponent = real.Branch();
    opponent->ApplyAction({});

    const auto target =
        opponent->GetCurrentPlayer()->opponent->GetHero()->GetGameTag(
            GameTag::ENTITY_ID);

    auto soulFire = Play(*opponent, "EX1_308");
    soulFire.targetID = target;

    const auto index = PolicyActions(opponent->GetGame()).Encode(soulFire);

    class DiscardEvaluator final : public BatchedEvaluator
    {
     public:
        std::size_t soulFire;
        std::vector<Observation> ownNext;

     private:
        std::vector<EvaluationResult> EvaluateBatch(
            std::span<const EvaluationInput> inputs) override
        {
            std::vector<EvaluationResult> results;

            for (const auto& input : inputs)
            {
                const auto turn =
                    input.observation.turn[ObservationSchema::TURN_NUMBER];

                if (turn == 3)
                {
                    ownNext.push_back(input.observation);
                }

                EvaluationResult result;
                result.priors.resize(PolicySchema::NUM_ACTIONS);
                result.priors[turn == 2 && input.legalMask[soulFire]
                                  ? soulFire
                                  : PolicySchema::END_TURN] = 1.0f;

                results.push_back(std::move(result));
            }

            return results;
        }
    } evaluator;

    evaluator.soulFire = index;

    SearchInformationSet(information, evaluator, { 128, 3 }, 1070);

    // Same board, health and hand counts; each different public discard is
    // nevertheless a distinct decision for the observer on the next turn.
    REQUIRE_GT(evaluator.ownNext.size(), 1);

    for (const auto& observation : evaluator.ownNext)
    {
        CHECK(observation == evaluator.ownNext.front());
    }
}

TEST_CASE("[InformationSetSearch] - ValuesFollowTheDecisionPlayer")
{
    for (const auto starter : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
    {
        const auto config = MirrorConfig(starter);
        ReplayGame real(config, 0);
        const auto information = Opening(config, real);

        RecordingEvaluator evaluator;
        evaluator.value = 0.25f;

        const auto result =
            SearchInformationSet(information, evaluator, { 32, 1 }, 1070);

        for (const auto& action : result.actions)
        {
            REQUIRE_GT(action.visitCount, 0);

            const double expected =
                action.actionIndex == PolicySchema::END_TURN ? -0.25 : 0.25;

            CHECK_EQ(action.GetMeanValue(), expected);
        }
    }
}

TEST_CASE("[InformationSetSearch] - LimitsValidationAndRootOnlyBudget")
{
    const auto config = MirrorConfig(PlayerType::PLAYER1);
    ReplayGame real(config, 0);
    const auto information = Opening(config, real);
    RecordingEvaluator evaluator;
    const auto ambient = Random::engine();

    CHECK_THROWS_AS(SearchInformationSet(information, evaluator, { 0, 1 }, 0),
                    std::invalid_argument);
    CHECK_THROWS_AS(SearchInformationSet(information, evaluator, { 1, 0 }, 0),
                    std::invalid_argument);

    for (const double exploration :
         { -1.0, std::numeric_limits<double>::quiet_NaN(),
           std::numeric_limits<double>::infinity() })
    {
        CHECK_THROWS_AS(SearchInformationSet(information, evaluator, { 1, 1 },
                                             0, exploration),
                        std::invalid_argument);
    }

    CHECK(evaluator.observations.empty());

    const auto result =
        SearchInformationSet(information, evaluator, { 1, 1 }, 0);

    CHECK_EQ(result.visitCount, 1);
    CHECK_EQ(evaluator.observations.size(), 1);
    REQUIRE(result.GetRootAction());
    CHECK_EQ(*result.GetRootAction(), PolicySchema::END_TURN);

    for (const auto& action : result.actions)
    {
        CHECK_EQ(action.visitCount, 0);
    }

    const auto preferredAction =
        PolicyActions(real.GetGame()).Encode(Play(real, "EX1_277"));

    evaluator.onlyAction = preferredAction;

    const auto preferred =
        SearchInformationSet(information, evaluator, { 1, 1 }, 0);

    CHECK_EQ(preferred.GetRootAction(),
             std::optional<std::size_t>{ preferredAction });

    auto invalid = information;
    ++invalid.observation.heroes[0][ObservationSchema::HEALTH];

    CHECK_THROWS_AS(SearchInformationSet(invalid, evaluator, { 2, 1 }, 0),
                    std::invalid_argument);
    CHECK(Random::engine() == ambient);
}
