// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/InputDataConverter.hpp>
#include <NeuralNet/NeuralNetworkInputImpl.hpp>

namespace RosettaTorch::NeuralNet
{
void NeuralNetworkInputImpl::AddData(const IInputGetter* getter)
{
    torch::Tensor hero, minion, standalone;
    InputDataConverter().Convert(getter, hero, minion, standalone);
    m_input.push_back({ hero, minion, standalone });
}

void NeuralNetworkInputImpl::Clear()
{
    m_input.clear();
}

const std::vector<std::array<torch::Tensor, 3>>&
NeuralNetworkInputImpl::GetData() const
{
    return m_input;
}
}  // namespace RosettaTorch::NeuralNet