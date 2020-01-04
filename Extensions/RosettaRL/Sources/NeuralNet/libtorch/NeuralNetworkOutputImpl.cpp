// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/libtorch/NeuralNetworkOutputImpl.hpp>

namespace RosettaTorch::NeuralNet
{
void NeuralNetworkOutputImpl::AddData(int label)
{
    std::vector<float> output;
    output.push_back(static_cast<float>(label));
    m_output.push_back(output);
}

void NeuralNetworkOutputImpl::Clear()
{
    m_output.clear();
}

const std::vector<std::vector<float>>& NeuralNetworkOutputImpl::GetData() const
{
    return m_output;
}
}  // namespace RosettaTorch::NeuralNet