// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/NeuralNetworkOutput.hpp>

namespace RosettaTorch::NeuralNet
{
NeuralNetworkOutput::NeuralNetworkOutput()
    : m_impl(new NeuralNetworkOutputImpl())
{
    // Do nothing
}

NeuralNetworkOutput::~NeuralNetworkOutput()
{
    delete m_impl;
}

void NeuralNetworkOutput::AddData(int label)
{
    m_impl->AddData(label);
}

void NeuralNetworkOutput::Clear()
{
    m_impl->Clear();
}
}  // namespace RosettaTorch::NeuralNet