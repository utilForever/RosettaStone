// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_CNN_MODEL_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_CNN_MODEL_HPP

#include <torch/torch.h>

namespace RosettaTorch::NeuralNet
{
//!
//! \brief CNNModel class.
//!
//! This class is a PyTorch model for CNN(Convolution Neural Network) that
//! inherits from torch::nn::Module.
//!
//!
class CNNModel : public torch::nn::Module
{
 public:
    //! Constructor.
    CNNModel();

    //! Encodes the information of two heros.
    //! \param x The tensor that has information of heros.
    //! \return The encoded torch tensor from \p x.
    torch::Tensor EncodeHero(torch::Tensor x);

    //! Encodes the minions' information from the two fields.
    //! \param x The tensor that has information of minions.
    //! \return The encoded torch tensor from \p x.
    torch::Tensor EncodeMinion(torch::Tensor x);

    //! Encodes the standalone information from the field.
    //! \param x The tensor that has information of 'standalone'.
    //! \return The encoded torch tensor from \p x.
    torch::Tensor EncodeStandalone(torch::Tensor x);

    //! The baseline CNN model.
    //! \param hero Inputs of the model.
    //! \param minion Inputs of the model.
    //! \param standalone Inputs of the model.
    //! \return Scaled torch tensor between [-1, 1].
    torch::Tensor forward(torch::Tensor hero, torch::Tensor minion,
                          torch::Tensor standalone);

 private:
    constexpr static int HERO_IN_DIM = 1;
    constexpr static int HERO_OUT_DIM = 1;

    constexpr static int MINION_IN_DIM = 7;
    constexpr static int MINION_OUT_DIM = 3;

    constexpr static int MINION_COUNT = 7;

    constexpr static int STANDALONE_IN_DIM = 17;

    constexpr static int CONCAT_UNIT = 2 * HERO_OUT_DIM +
                                       2 * MINION_COUNT * MINION_OUT_DIM +
                                       STANDALONE_IN_DIM;

    constexpr static int FC_UNIT = 10;

    torch::nn::Conv1d m_heroConv = torch::nn::Conv1d(
        torch::nn::Conv1dOptions(HERO_IN_DIM, HERO_OUT_DIM, 1));

    torch::nn::Conv1d m_minionConv = torch::nn::Conv1d(
        torch::nn::Conv1dOptions(MINION_IN_DIM, MINION_OUT_DIM, 1));

    torch::nn::Linear m_fc1 = torch::nn::Linear(CONCAT_UNIT, FC_UNIT);
    torch::nn::Linear m_fc2 = torch::nn::Linear(FC_UNIT, 1);
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_CNN_MODEL_HPP