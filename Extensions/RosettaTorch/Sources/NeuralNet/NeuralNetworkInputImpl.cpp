// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/NeuralNetworkInputImpl.hpp>

namespace RosettaTorch::NeuralNet
{
void NeuralNetworkInputImpl::AddData([[maybe_unused]] const IInputGetter* getter)
{
    torch::Tensor input;
    // TODO: Implement InputDataConverter
    m_input.push_back(input);
}

void NeuralNetworkInputImpl::Clear()
{
    m_input.clear();
}

const auto& NeuralNetworkInputImpl::GetData() const
{
    return m_input;
}
}  // namespace RosettaTorch::NeuralNet