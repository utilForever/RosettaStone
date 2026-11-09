// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Agents/PUCTSearch.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>

#include <limits>
#include <stdexcept>

using namespace RosettaStone;
using namespace PlayMode;

namespace
{
using Policy = std::array<float, PolicySchema::NUM_ACTIONS>;

PolicySchema::LegalMask Mask(std::initializer_list<std::size_t> actions)
{
    PolicySchema::LegalMask mask{};

    for (const auto action : actions)
    {
        mask.at(action) = 1;
    }

    return mask;
}
}  // namespace

TEST_CASE("[PUCTSearch] - LegalExpansionAndRootPrior")
{
    PUCTSearch search({ 1, 4 });

    CHECK_FALSE(search.GetRootAction());

    const auto root = search.SelectLeaf();

    REQUIRE(root);
    CHECK(root->empty());

    Policy priors{};
    priors[0] = 1000.0f;  // An illegal action cannot receive a child or prior.
    priors[7] = 1.0f;
    priors[42] = 3.0f;

    search.Expand(PlayerType::PLAYER1,
                  Mask({ 7, 42, PolicySchema::NUM_ACTIONS - 1 }), priors, 0.5);

    const auto& nodes = search.GetNodes();

    REQUIRE_EQ(nodes.size(), 4);
    REQUIRE_EQ(nodes[0].children.size(), 3);
    CHECK_EQ(nodes[0].visitCount, 1);
    CHECK_EQ(nodes[0].GetMeanValue(), 0.5);
    CHECK_EQ(nodes[1].actionIndex, 7);
    CHECK_EQ(nodes[1].prior, 0.25);
    CHECK_EQ(nodes[2].actionIndex, 42);
    CHECK_EQ(nodes[2].prior, 0.75);
    CHECK_EQ(nodes[3].actionIndex, PolicySchema::NUM_ACTIONS - 1);
    CHECK_EQ(nodes[3].prior, 0.0);
    CHECK_EQ(nodes[1].visitCount, 0);
    CHECK_EQ(nodes[1].GetMeanValue(), 0.0);

    CHECK_EQ(search.GetRootAction(), std::optional<std::size_t>{ 42 });
    CHECK_FALSE(search.SelectLeaf());
}

TEST_CASE("[PUCTSearch] - ZeroAndLargeLegalWeights")
{
    for (const float weight : { 0.0f, std::numeric_limits<float>::max() })
    {
        PUCTSearch search({ 1, 1 });

        REQUIRE(search.SelectLeaf());

        Policy priors{};
        priors[0] = 1000.0f;
        priors[2] = weight;
        priors[9] = weight;

        search.Expand(PlayerType::PLAYER1, Mask({ 2, 9 }), priors, 0.0);

        const auto& nodes = search.GetNodes();

        REQUIRE_EQ(nodes.size(), 3);
        CHECK_EQ(nodes[1].prior, 0.5);
        CHECK_EQ(nodes[2].prior, 0.5);

        CHECK_EQ(search.GetRootAction(), std::optional<std::size_t>{ 2 });
    }
}

TEST_CASE("[PUCTSearch] - SelectionUsesPUCTAndParentPerspective")
{
    PUCTSearch search({ 4, 3 });

    REQUIRE(search.SelectLeaf());

    Policy priors{};
    priors[1] = 3.0f;
    priors[2] = 1.0f;

    search.Expand(PlayerType::PLAYER1, Mask({ 1, 2 }), priors, 0.0);

    auto path = search.SelectLeaf();

    REQUIRE(path);
    CHECK(*path == std::vector<std::size_t>{ 1 });

    search.Expand(PlayerType::PLAYER1, Mask({ 3 }), Policy{}, -0.5);

    // At N(root)=2: scores are -0.5 + 0.75*sqrt(2)/2 and 0.25*sqrt(2).
    path = search.SelectLeaf();

    REQUIRE(path);
    CHECK(*path == std::vector<std::size_t>{ 2 });

    search.Expand(PlayerType::PLAYER2, Mask({ 3 }), Policy{}, 0.25);

    // At N(root)=3: action 2's Q is -0.25 for player 1, so action 1 wins.
    path = search.SelectLeaf();

    REQUIRE(path);
    CHECK(*path == std::vector<std::size_t>{ 1, 3 });

    search.SetTerminal(PlayerType::PLAYER1, 0.8);

    CHECK_FALSE(search.SelectLeaf());

    const auto& nodes = search.GetNodes();

    CHECK_EQ(nodes[0].visitCount, 4);
    CHECK_EQ(nodes[0].totalValue, doctest::Approx(0.05));
    CHECK_EQ(nodes[1].visitCount, 2);
    CHECK_EQ(nodes[1].GetMeanValue(), doctest::Approx(0.15));
    CHECK_EQ(nodes[2].visitCount, 1);
    CHECK_EQ(nodes[2].GetMeanValue(), 0.25);

    CHECK_EQ(search.GetRootAction(), std::optional<std::size_t>{ 1 });
}

TEST_CASE("[PUCTSearch] - BackupAcrossSamePlayerActionsAndTurnChanges")
{
    for (const auto actor : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
    {
        const auto other = actor == PlayerType::PLAYER1 ? PlayerType::PLAYER2
                                                        : PlayerType::PLAYER1;
        PUCTSearch search({ 6, 8 });
        const std::array players{ actor, actor, other, other, actor };

        for (std::size_t depth = 0; depth < players.size(); ++depth)
        {
            const auto path = search.SelectLeaf();

            REQUIRE(path);
            CHECK_EQ(path->size(), depth);

            if (depth + 1 == players.size())
            {
                search.SetTerminal(players[depth], 1.0);
            }
            else
            {
                search.Expand(players[depth], Mask({ 1 }), Policy{}, 0.0);
            }
        }

        // The last simulation revisits the cached terminal leaf.
        CHECK_FALSE(search.SelectLeaf());

        const auto& nodes = search.GetNodes();

        REQUIRE_EQ(nodes.size(), players.size());

        for (std::size_t i = 0; i < players.size(); ++i)
        {
            const double expected = players[i] == actor ? 2.0 : -2.0;

            CHECK_EQ(nodes[i].visitCount, 6 - i);
            CHECK_EQ(nodes[i].totalValue, expected);
            CHECK_EQ(nodes[i].GetMeanValue(), expected / (6 - i));
        }

        CHECK(nodes.back().terminal);
        CHECK(nodes.back().children.empty());
    }
}

TEST_CASE("[PUCTSearch] - TerminalRootsAndLeaves")
{
    for (const double reward : { -1.0, 0.0, 1.0 })
    {
        PUCTSearch root({ 10, 2 });

        REQUIRE(root.SelectLeaf());

        root.SetTerminal(PlayerType::PLAYER2, reward);

        CHECK_FALSE(root.SelectLeaf());
        CHECK_FALSE(root.GetRootAction());
        REQUIRE_EQ(root.GetNodes().size(), 1);
        CHECK_EQ(root.GetNodes()[0].visitCount, 1);
        CHECK_EQ(root.GetNodes()[0].GetMeanValue(), reward);

        PUCTSearch search({ 5, 2 });

        REQUIRE(search.SelectLeaf());

        search.Expand(PlayerType::PLAYER1, Mask({ 4 }), Policy{}, 0.0);

        REQUIRE(search.SelectLeaf());

        search.SetTerminal(PlayerType::PLAYER2, reward);

        CHECK_FALSE(search.SelectLeaf());
        REQUIRE_EQ(search.GetNodes().size(), 2);
        CHECK_EQ(search.GetNodes()[0].totalValue, -4.0 * reward);
        CHECK_EQ(search.GetNodes()[1].visitCount, 4);
        CHECK_EQ(search.GetNodes()[1].GetMeanValue(), reward);
    }
}

TEST_CASE("[PUCTSearch] - DeterministicTiesAndVisitChoice")
{
    for (int repetition = 0; repetition < 3; ++repetition)
    {
        PUCTSearch search({ 33, 3 });

        REQUIRE(search.SelectLeaf());

        search.Expand(PlayerType::PLAYER1, Mask({ 9, 2 }), Policy{}, 0.0);

        auto path = search.SelectLeaf();

        REQUIRE(path);
        CHECK(*path == std::vector<std::size_t>{ 2 });

        search.SetTerminal(PlayerType::PLAYER1, 0.0);
        path = search.SelectLeaf();

        REQUIRE(path);
        CHECK(*path == std::vector<std::size_t>{ 9 });

        search.SetTerminal(PlayerType::PLAYER1, 0.0);

        CHECK_FALSE(search.SelectLeaf());
        CHECK_EQ(search.GetNodes()[0].visitCount, 33);
        CHECK_EQ(search.GetNodes()[1].visitCount, 16);
        CHECK_EQ(search.GetNodes()[2].visitCount, 16);
        CHECK_EQ(search.GetRootAction(), std::optional<std::size_t>{ 2 });
    }

    // Visit count takes precedence over the prior at the root.
    PUCTSearch search({ 12, 2 });

    REQUIRE(search.SelectLeaf());

    Policy priors{};
    priors[2] = 3.0f;
    priors[9] = 1.0f;

    search.Expand(PlayerType::PLAYER1, Mask({ 2, 9 }), priors, 0.0);

    REQUIRE(search.SelectLeaf());

    search.SetTerminal(PlayerType::PLAYER1, -1.0);

    const auto path = search.SelectLeaf();

    REQUIRE(path);
    CHECK(*path == std::vector<std::size_t>{ 9 });

    search.SetTerminal(PlayerType::PLAYER1, 1.0);

    CHECK_FALSE(search.SelectLeaf());
    CHECK_EQ(search.GetRootAction(), std::optional<std::size_t>{ 9 });
}

TEST_CASE("[PUCTSearch] - DepthAndSimulationLimits")
{
    PUCTSearch search({ 7, 1 }, 0.0);

    REQUIRE(search.SelectLeaf());

    search.Expand(PlayerType::PLAYER1, Mask({ 1 }), Policy{}, 0.0);
    const auto path = search.SelectLeaf();

    REQUIRE(path);
    CHECK_EQ(path->size(), 1);

    search.Expand(PlayerType::PLAYER1, Mask({ 2 }), Policy{}, 0.25);

    // Depth one reuses its original evaluation, without creating grandchildren.
    CHECK_FALSE(search.SelectLeaf());
    CHECK_FALSE(search.SelectLeaf());

    const auto& nodes = search.GetNodes();

    REQUIRE_EQ(nodes.size(), 2);
    CHECK_EQ(nodes[0].visitCount, 7);
    CHECK_EQ(nodes[0].totalValue, 1.5);
    CHECK_EQ(nodes[1].visitCount, 6);
    CHECK_EQ(nodes[1].GetMeanValue(), 0.25);
    CHECK_FALSE(nodes[1].terminal);
    CHECK(nodes[1].children.empty());
}

TEST_CASE("[PUCTSearch] - InvalidInputsLeavePendingLeafUnchanged")
{
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double infinity = std::numeric_limits<double>::infinity();

    CHECK_THROWS_AS(PUCTSearch({ 0, 1 }), std::invalid_argument);
    CHECK_THROWS_AS(PUCTSearch({ 1, 0 }), std::invalid_argument);

    for (const double exploration : { -1.0, nan, infinity })
    {
        CHECK_THROWS_AS(PUCTSearch({ 1, 1 }, exploration),
                        std::invalid_argument);
    }

    PUCTSearch search({ 1, 1 });
    const auto mask = Mask({ 1 });

    CHECK_THROWS_AS(search.Expand(PlayerType::PLAYER1, mask, Policy{}, 0.0),
                    std::logic_error);
    CHECK_THROWS_AS(search.SetTerminal(PlayerType::PLAYER1, 0.0),
                    std::logic_error);
    REQUIRE(search.SelectLeaf());
    CHECK_THROWS_AS(search.SelectLeaf(), std::logic_error);

    for (const double value : { -1.1, 1.1, nan, infinity })
    {
        CHECK_THROWS_AS(
            search.Expand(PlayerType::PLAYER1, mask, Policy{}, value),
            std::invalid_argument);
        CHECK_THROWS_AS(search.SetTerminal(PlayerType::PLAYER1, value),
                        std::invalid_argument);
    }

    for (const auto player : { PlayerType::INVALID, PlayerType::RANDOM })
    {
        CHECK_THROWS_AS(search.Expand(player, mask, Policy{}, 0.0),
                        std::invalid_argument);
        CHECK_THROWS_AS(search.SetTerminal(player, 0.0), std::invalid_argument);
    }

    for (const auto size :
         { PolicySchema::NUM_ACTIONS - 1, PolicySchema::NUM_ACTIONS + 1 })
    {
        CHECK_THROWS_AS(search.Expand(PlayerType::PLAYER1, mask,
                                      std::vector<float>(size), 0.0),
                        std::invalid_argument);
    }

    for (const float prior : { -1.0f, std::numeric_limits<float>::quiet_NaN(),
                               std::numeric_limits<float>::infinity() })
    {
        Policy priors{};
        priors[0] = prior;  // Even masked evaluator entries must be valid.

        CHECK_THROWS_AS(search.Expand(PlayerType::PLAYER1, mask, priors, 0.0),
                        std::invalid_argument);
    }

    auto invalidMask = mask;
    invalidMask[0] = 2;

    CHECK_THROWS_AS(
        search.Expand(PlayerType::PLAYER1, invalidMask, Policy{}, 0.0),
        std::invalid_argument);
    CHECK_THROWS_AS(search.Expand(PlayerType::PLAYER1, Mask({}), Policy{}, 0.0),
                    std::invalid_argument);
    REQUIRE_EQ(search.GetNodes().size(), 1);
    CHECK_EQ(search.GetNodes()[0].visitCount, 0);
    CHECK_FALSE(search.GetNodes()[0].expanded);
    CHECK_FALSE(search.GetRootAction());

    search.Expand(PlayerType::PLAYER1, mask, Policy{}, 0.0);

    CHECK_FALSE(search.SelectLeaf());
    CHECK_THROWS_AS(search.SetTerminal(PlayerType::PLAYER1, 0.0),
                    std::logic_error);
}

TEST_CASE("[PUCTSearch] - SeededReplayPolicyIntegration")
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::MAGE;
    config.player1Deck.fill(Cards::FindCardByID("CS2_231"));
    config.player2Deck = config.player1Deck;

    std::vector<PUCTNode> expected;
    std::optional<std::size_t> expectedAction;

    for (int repetition = 0; repetition < 2; ++repetition)
    {
        ReplayGame root(config, 1067);
        const PolicyActions rootPolicy(root.GetGame());
        PUCTSearch search({ 24, 2 });

        while (const auto path = search.SelectLeaf())
        {
            auto branch = root.Branch();

            for (const auto action : *path)
            {
                const PolicyActions policy(branch->GetGame());
                branch->ApplyAction(policy.Decode(action));
            }

            const auto player = branch->GetCurrentPlayer()->playerType;

            if (branch->GetGame().state == State::COMPLETE)
            {
                search.SetTerminal(player, branch->GetReward(player));
            }
            else
            {
                const PolicyActions policy(branch->GetGame());

                search.Expand(player, policy.GetLegalMask(), Policy{}, 0.0);
            }
        }

        REQUIRE(search.GetRootAction());
        CHECK_EQ(rootPolicy.GetLegalMask()[*search.GetRootAction()], 1);
        CHECK_NOTHROW(
            root.ApplyAction(rootPolicy.Decode(*search.GetRootAction())));
        CHECK_EQ(search.GetNodes()[0].visitCount, 24);

        if (repetition == 0)
        {
            expected = search.GetNodes();
            expectedAction = search.GetRootAction();
            continue;
        }

        CHECK_EQ(search.GetRootAction(), expectedAction);

        const auto& actual = search.GetNodes();

        REQUIRE_EQ(actual.size(), expected.size());

        for (std::size_t i = 0; i < actual.size(); ++i)
        {
            CHECK_EQ(actual[i].actionIndex, expected[i].actionIndex);
            CHECK_EQ(actual[i].player, expected[i].player);
            CHECK_EQ(actual[i].prior, expected[i].prior);
            CHECK_EQ(actual[i].visitCount, expected[i].visitCount);
            CHECK_EQ(actual[i].totalValue, expected[i].totalValue);
            CHECK(actual[i].children == expected[i].children);
        }
    }
}
