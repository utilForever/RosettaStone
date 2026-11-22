// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_RL_TESTS_REPLAY_TRAINING_BATCH_HPP
#define ROSETTASTONE_RL_TESTS_REPLAY_TRAINING_BATCH_HPP

#include <RosettaRL/PolicyValueNetwork.hpp>

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>

#include <array>

namespace RosettaStone::RL::Tests
{
inline std::array<torch::Tensor, 3> ReplayTrainingBatch()
{
    using namespace PlayMode;

    Cards::GetInstance();

    GameConfig config;
    config.formatType = FormatType::WILD;
    config.player1Class = config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = false;
    config.player1Deck.fill(
        Cards::FindCardByID("CS2_200"));  // Boulderfist Ogre
    config.player2Deck = config.player1Deck;

    ReplayGame replay(config, 1074);
    const auto& game = replay.GetGame();
    const auto firstTurn = EncodeObservation(game);

    replay.ApplyAction(PlayerAction{});

    const auto observations = EncodeObservationBatch(
        std::array{ firstTurn, EncodeObservation(game) });
    const auto actions = EnumerateActions(game);

    TORCH_CHECK(actions.size() == 2 &&
                    actions.back().type == PlayerActionType::PLAY_CARD,
                "Expected End Turn and The Coin");

    const auto coin = PolicyActions(game).Encode(actions.back());
    auto policy = torch::zeros({ 2, PolicySchema::NUM_ACTIONS });

    policy[0][PolicySchema::END_TURN] = 1.0;
    policy[1][PolicySchema::END_TURN] = 0.25;
    policy[1][coin] = 0.75;

    return { observations, policy, torch::tensor({ 1.0f, -1.0f }) };
}
}  // namespace RosettaStone::RL::Tests

#endif  // ROSETTASTONE_RL_TESTS_REPLAY_TRAINING_BATCH_HPP
