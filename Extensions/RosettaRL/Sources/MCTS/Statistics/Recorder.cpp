// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Statistics/Recorder.hpp>

namespace RosettaTorch::MCTS
{
void SuccessRateRecorder::ReportSuccess()
{
    ++m_success;
    ++m_total;
}

void SuccessRateRecorder::ReportFail()
{
    ++m_total;
}

int SuccessRateRecorder::GetSuccessCount() const
{
    return m_success;
}

int SuccessRateRecorder::GetTotalCount() const
{
    return m_total;
}

double SuccessRateRecorder::GetSuccessRate() const
{
    if (m_total == 0)
    {
        return 0.0;
    }

    return static_cast<double>(m_success) / m_total;
}
}  // namespace RosettaTorch::MCTS