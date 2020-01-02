// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Evaluation/Evaluator.hpp>

namespace RosettaTorch::AlphaZero::Evaluation
{
void Evaluator::BeforeRun(const std::string& bestNetPath,
                          const std::string& competitorNetPath,
                          CompetitionResult& result)
{
    m_bestNetPath = bestNetPath;
    m_competitorNetPath = competitorNetPath;
    m_result = &result;
}

void Evaluator::AfterRun()
{
    // Do nothing
}
}  // namespace RosettaTorch::AlphaZero::Evaluation