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
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_CNN_MODEL_HPP