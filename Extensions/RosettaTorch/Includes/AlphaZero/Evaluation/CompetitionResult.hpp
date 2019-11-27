// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_COMPETITION_RESULT_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_COMPETITION_RESULT_HPP

#include <atomic>

namespace RosettaTorch::AlphaZero::Evaluation
{
//!
//! \brief CompetitionResult class.
//!
//! This class holds the result of the competition.
//!
class CompetitionResult
{
 public:
    //! Clears the result of the competition.
    void Clear();

    //! Adds the result of the competition.
    //! \param win The flag indicates that whether the competitor wins.
    void AddResult(bool win);

    //! Gets the total number of games.
    //! \return The total number of games.
    std::size_t GetTotal() const;

    //! Gets the number of competitor wins.
    //! \return The number of competitor wins.
    std::size_t GetWin() const;

 private:
    std::atomic<std::size_t> m_totalGames = 0;
    std::atomic<std::size_t> m_competitorWins = 0;
};
}  // namespace RosettaTorch::AlphaZero::Evaluation

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_COMPETITION_RESULT_HPP