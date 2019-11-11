// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/NeuralNetworkStateValue.hpp>

namespace RosettaTorch::MCTS
{
NeuralNetworkStateValue::NeuralNetworkStateValue(const Config& config)
{
    m_net.Load(config.neuralNetPath, config.isNeuralNetRandom);
}

StateValue NeuralNetworkStateValue::GetStateValue(const Board& board)
{
    return GetStateValue(board.RevealHiddenInfoForSimulation());
}

StateValue NeuralNetworkStateValue::GetStateValue(const Game& game)
{
    m_curPlayerViewer.Reset(game);

    float score = static_cast<float>(m_net.Predict(&m_curPlayerViewer));
    score = std::clamp(score, -1.0f, 1.0f);

    StateValue ret;
    ret.SetValue(score, game.GetCurrentPlayer()->playerType);
    return ret;
}
}  // namespace RosettaTorch::MCTS