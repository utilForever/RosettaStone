// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/tiny-dnn/InputDataConverter.hpp>
#include <NeuralNet/tiny-dnn/NeuralNetworkInputImpl.hpp>

namespace RosettaTorch::NeuralNet
{
void NeuralNetworkInputImpl::AddData(const IInputGetter* getter)
{
    tiny_dnn::tensor_t input;
    InputDataConverter().Convert(getter, input);
    m_input.push_back(input);
}

void NeuralNetworkInputImpl::Clear()
{
    m_input.clear();
}

const std::vector<tiny_dnn::tensor_t>& NeuralNetworkInputImpl::GetData() const
{
    return m_input;
}
}  // namespace RosettaTorch::NeuralNet