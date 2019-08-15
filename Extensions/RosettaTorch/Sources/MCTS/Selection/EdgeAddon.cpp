// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Commons/Constants.hpp>
#include <MCTS/Selection/EdgeAddon.hpp>

namespace RosettaTorch::MCTS
{
EdgeAddon::EdgeAddon() : m_chosenTimes(0), m_credit(0), m_total(0)
{
    // Do nothing
}

void EdgeAddon::AddChosenTimes(int val)
{
    m_chosenTimes += val;
}

std::int64_t EdgeAddon::GetChosenTimes() const
{
    return m_chosenTimes.load();
}

float EdgeAddon::GetAverageCredit() const
{
    const auto totalLoad = m_total.load();
    const float ret = static_cast<float>(m_credit.load()) / totalLoad;

    return ret;
}

void EdgeAddon::AddCredit(float score, int repeatTimes)
{
    const int totalIncrement = CREDIT_GRANULARITY;
    const int creditIncrement = static_cast<int>(score * CREDIT_GRANULARITY);

    // These two fields are not updated in an atomic operation.
    // But this should be fine...
    m_total += static_cast<std::int64_t>(totalIncrement * repeatTimes);
    m_credit += static_cast<std::int64_t>(creditIncrement * repeatTimes);
}

std::int64_t EdgeAddon::GetTotal() const
{
    return m_total.load();
}
}  // namespace RosettaTorch::MCTS