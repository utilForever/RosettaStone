// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Evaluation/CompetitionResult.hpp>

namespace RosettaTorch::AlphaZero::Evaluation
{
void CompetitionResult::Clear()
{
    m_totalGames = 0;
    m_competitorWins = 0;
}

void CompetitionResult::AddResult(bool win)
{
    ++m_totalGames;

    if (win)
    {
        ++m_competitorWins;
    }
}

std::size_t CompetitionResult::GetTotal() const
{
    return m_totalGames.load();
}

std::size_t CompetitionResult::GetWin() const
{
    return m_competitorWins.load();
}
}  // namespace RosettaTorch::AlphaZero::Evaluation