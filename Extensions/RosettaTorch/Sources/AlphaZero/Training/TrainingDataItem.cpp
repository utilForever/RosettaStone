// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Training/TrainingDataItem.hpp>

#include <utility>

namespace RosettaTorch::AlphaZero
{
TrainingDataItem::TrainingDataItem(Judges::JSON::NeuralNetInputGetter input,
                                   int label)
    : m_input(std::move(input)), m_label(label)
{
    // Do nothing
}

const Judges::JSON::NeuralNetInputGetter& TrainingDataItem::GetInput() const
{
    return m_input;
}

int TrainingDataItem::GetLabel() const
{
    return m_label;
}
}  // namespace RosettaTorch::AlphaZero