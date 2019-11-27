// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Training/TrainingData.hpp>

namespace RosettaTorch::AlphaZero
{
void TrainingData::Initialize(std::size_t capacity)
{
    m_data.Initialize(capacity);
}

std::size_t TrainingData::Capacity() const
{
    return m_data.Capacity();
}

std::size_t TrainingData::Size() const
{
    return m_size.load();
}

void TrainingData::Push(std::shared_ptr<TrainingDataItem> item)
{
    m_data.AllocateNext().Write(std::move(item));
    ++m_size;
}
}  // namespace RosettaTorch::AlphaZero