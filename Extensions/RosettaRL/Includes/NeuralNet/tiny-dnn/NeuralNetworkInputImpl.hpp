// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_INPUT_IMPL_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_INPUT_IMPL_HPP

#include <NeuralNet/IInputGetter.hpp>

#include <tiny_dnn/tiny_dnn.h>

#include <vector>

namespace RosettaTorch::NeuralNet
{
//!
//! \brief NeuralNetworkInputImpl class.
//!
//! This class is implementation code of NeuralNetworkInput class.
//!
class NeuralNetworkInputImpl
{
 public:
    //! Adds data to the tensor.
    //! \param getter The input getter to get the value of the field.
    void AddData(const IInputGetter* getter);

    //! Clears data of the tensor.
    void Clear();

    //! Returns data in the tensor.
    //! \return Data in the tensor.
    const std::vector<tiny_dnn::tensor_t>& GetData() const;

 private:
    std::vector<tiny_dnn::tensor_t> m_input;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_INPUT_IMPL_HPP