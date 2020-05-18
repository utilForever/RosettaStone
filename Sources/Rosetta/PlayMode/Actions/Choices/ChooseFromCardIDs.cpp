// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/Choices/ChooseFromCardIDs.hpp>

namespace RosettaStone::PlayMode
{
ChooseFromCardIDs::ChooseFromCardIDs(const std::vector<std::size_t>& cardIDs)
    : m_cardIDs(cardIDs)
{
    // Do nothing
}

std::size_t ChooseFromCardIDs::Get(std::size_t idx) const
{
    return m_cardIDs[idx];
}

bool ChooseFromCardIDs::IsEmpty() const
{
    return m_cardIDs.empty();
}

std::size_t ChooseFromCardIDs::Size() const
{
    return m_cardIDs.size();
}

void ChooseFromCardIDs::Begin()
{
    m_iter = m_cardIDs.begin();
}

std::size_t ChooseFromCardIDs::Get() const
{
    return *m_iter;
}

void ChooseFromCardIDs::StepNext()
{
    ++m_iter;
}

bool ChooseFromCardIDs::IsEnd() const
{
    return m_iter == m_cardIDs.end();
}
}  // namespace RosettaStone::PlayMode