// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/Choices/ChooseFromNumbers.hpp>

namespace RosettaStone::PlayMode
{
ChooseFromNumbers::ChooseFromNumbers(std::size_t max) : m_max(max), m_iter(0)
{
    // Do nothing
}

std::size_t ChooseFromNumbers::Get(std::size_t idx)
{
    return static_cast<int>(idx);
}

bool ChooseFromNumbers::IsEmpty() const
{
    return m_max <= 0;
}

std::size_t ChooseFromNumbers::Size() const
{
    return m_max;
}

void ChooseFromNumbers::Begin()
{
    m_iter = 0;
}

std::size_t ChooseFromNumbers::Get() const
{
    return m_iter;
}

void ChooseFromNumbers::StepNext()
{
    ++m_iter;
}

bool ChooseFromNumbers::IsEnd() const
{
    return m_iter >= m_max;
}
}  // namespace RosettaStone::PlayMode