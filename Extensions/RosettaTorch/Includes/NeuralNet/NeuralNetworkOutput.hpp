// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_OUTPUT_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_OUTPUT_HPP

#include <NeuralNet/NeuralNetworkOutputImpl.hpp>

namespace RosettaTorch::NeuralNet
{
//!
//! \brief NeuralNetworkOutput class.
//!
//! This class is output layer of the neural network that contains AddData()
//! and Clear() method.
//!
class NeuralNetworkOutput
{
    friend class NeuralNetwork;

 public:
    //! Constructor.
    NeuralNetworkOutput();

    //! Destructor.
    ~NeuralNetworkOutput();

    //! Deleted copy constructor.
    NeuralNetworkOutput(const NeuralNetworkOutput&) = delete;

    //! Deleted move constructor.
    NeuralNetworkOutput(NeuralNetworkOutput&&) noexcept = delete;

    //! Deleted copy assignment operator.
    NeuralNetworkOutput& operator=(const NeuralNetworkOutput&) = delete;

    //! Deleted move assignment operator.
    NeuralNetworkOutput& operator=(NeuralNetworkOutput&&) noexcept = delete;

    //! Adds data to the vector.
    //! \param label The value to add to the vector.
    void AddData(int label);

    //! Clears data of the vector.
    void Clear();

 private:
    NeuralNetworkOutputImpl* m_impl;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_OUTPUT_HPP