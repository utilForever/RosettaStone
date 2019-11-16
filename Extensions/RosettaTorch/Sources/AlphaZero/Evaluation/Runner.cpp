// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Evaluation/Runner.hpp>

namespace RosettaTorch::AlphaZero::Evaluation
{
void Runner::BeforeRun(const RunOptions& runOptions,
                       const std::string& bestNetPath,
                       const std::string& competitorNetPath,
                       CompetitionResult& result)
{
}

const CompetitionResult& Runner::AfterRun() const
{
    return m_result;
}
}  // namespace RosettaTorch::AlphaZero::Evaluation