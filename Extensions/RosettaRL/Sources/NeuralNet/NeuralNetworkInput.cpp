// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/NeuralNetworkInput.hpp>

#if defined(ROSETTARL_ML_LIBRARY_LIBTORCH)
#include <NeuralNet/libtorch/NeuralNetworkInputImpl.hpp>
#elif defined(ROSETTARL_ML_LIBRARY_TINY_DNN)
#include <Neuralnet/tiny-dnn/NeuralNetworkInputImpl.hpp>
#endif

namespace RosettaTorch::NeuralNet
{
NeuralNetworkInput::NeuralNetworkInput() : m_impl(new NeuralNetworkInputImpl())
{
    // Do nothing
}

NeuralNetworkInput::~NeuralNetworkInput()
{
    delete m_impl;
}

void NeuralNetworkInput::AddData(const IInputGetter* getter)
{
    m_impl->AddData(getter);
}

void NeuralNetworkInput::Clear()
{
    m_impl->Clear();
}
}  // namespace RosettaTorch::NeuralNet