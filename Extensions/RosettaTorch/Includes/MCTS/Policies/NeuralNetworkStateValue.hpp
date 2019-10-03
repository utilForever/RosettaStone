// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_STATE_VALUE_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_STATE_VALUE_HPP

#include <MCTS/Commons/Config.hpp>
#include <MCTS/Commons/Types.hpp>
#include <NeuralNet/GameDataBridge.hpp>
#include <NeuralNet/NeuralNetwork.hpp>

#include <Rosetta/Views/Board.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief NeuralNetworkStateValue class.
//!
//! This class contains getters for the state value.
//!
class NeuralNetworkStateValue
{
 public:
    //! Constructs neural network state value with given \p config.
    //! \param config The config for neural network.
    explicit NeuralNetworkStateValue(const Config& config);

    //! Returns the state value.
    //! \param board The game board.
    //! \return The state value.
    StateValue GetStateValue(const Board& board);

    //! Returns the state value.
    //! \param game The game context.
    //! \return The state value.
    StateValue GetStateValue(const Game& game);

 private:
    NeuralNet::NeuralNetwork m_net;
    NeuralNet::GameDataBridge m_curPlayerViewer;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_STATE_VALUE_HPP