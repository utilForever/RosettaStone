// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_INPUT_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_INPUT_HPP

#include <NeuralNet/IInputGetter.hpp>

namespace RosettaTorch::NeuralNet
{
class NeuralNetworkInputImpl;

//!
//! \brief NeuralNetworkInput class.
//!
//! This class is input layer of the neural network that contains AddData()
//! and Clear() method.
//!
class NeuralNetworkInput
{
    friend class NeuralNetwork;

 public:
    //! Constructor.
    NeuralNetworkInput();

    //! Destructor.
    ~NeuralNetworkInput();

    //! Deleted copy constructor.
    NeuralNetworkInput(const NeuralNetworkInput&) = delete;

    //! Deleted move constructor.
    NeuralNetworkInput(NeuralNetworkInput&&) noexcept = delete;

    //! Deleted copy assignment operator.
    NeuralNetworkInput& operator=(const NeuralNetworkInput&) = delete;

    //! Deleted move assignment operator.
    NeuralNetworkInput& operator=(NeuralNetworkInput&&) noexcept = delete;

    //! Adds data to the tensor.
    //! \param getter The input getter to get the value of the field.
    void AddData(const IInputGetter* getter);

    //! Clears data of the tensor.
    void Clear();

 private:
    NeuralNetworkInputImpl* m_impl;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_INPUT_HPP