// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_RECORDER_HPP
#define ROSETTASTONE_TORCH_MCTS_RECORDER_HPP

#include <atomic>

namespace RosettaTorch::MCTS
{
//!
//! \brief SuccessRateRecorder class.
//!
//! This class records success rate of something.
//!
class SuccessRateRecorder
{
 public:
    //! Reports something success.
    void ReportSuccess();

    //! Reports something fail.
    void ReportFail();

    //! Returns the success count.
    //! \return The success count.
    int GetSuccessCount() const;

    //! Returns the total count.
    //! \return The total count.
    int GetTotalCount() const;

    //! Returns the success rate.
    //! \return The success rate.
    double GetSuccessRate() const;

 private:
    std::atomic<int> m_success = 0;
    std::atomic<int> m_total = 0;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_RECORDER_HPP