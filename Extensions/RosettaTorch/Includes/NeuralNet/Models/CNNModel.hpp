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
    torch::Tensor encodeHero(torch::Tensor x);

    //! Encodes the minions' information from the two fields.
    //! \param x The tensor that has information of minions.
    //! \return The encoded torch tensor from \p x.
    torch::Tensor encodeMinion(torch::Tensor x);

    //! Encodes the standalone information from the field.
    //! \param x The tensor that has information of 'standalone'.
    //! \return The encoded torch tensor from \p x.
    torch::Tensor encodeStandalone(torch::Tensor x);

    //! Baseline dnn model.
    //! \param hero Inputs of the model.
    //! \param minion Inputs of the model.
    //! \param standalone Inputs of the model.
    //! \return Scaled torch tensor between [-1, 1].
    torch::Tensor forward(torch::Tensor hero, torch::Tensor minion,
                          torch::Tensor standalone);

 private:
    static constexpr std::size_t hero_in_dim = 1;
    static constexpr std::size_t hero_out_dim = 1;

    static constexpr std::size_t minion_in_dim = 7;
    static constexpr std::size_t minion_out_dim = 3;

    static constexpr std::size_t minion_count = 7;

    static constexpr std::size_t standalone_in_dim = 17;

    static constexpr std::size_t concat_unit =
        2 * hero_out_dim + 2 * minion_count * minion_out_dim +
        standalone_in_dim;

    static constexpr std::size_t fc_unit = 10;

    torch::nn::Conv1d heroConv1 = 
        torch::nn::Conv1d(hero_in_dim, hero_out_dim, 1);

    torch::nn::Conv1d minionConv1 =
        torch::nn::Conv1d(minion_in_dim, minion_out_dim, 1);

    torch::nn::Linear fc1 = torch::nn::Linear(concat_unit, fc_unit);
    torch::nn::Linear fc2 = torch::nn::Linear(fc_unit, 1);
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_CNN_MODEL_HPP