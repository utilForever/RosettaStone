// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_STATISTICS_HPP
#define ROSETTASTONE_TORCH_MCTS_STATISTICS_HPP

#include <MCTS/Commons/Constants.hpp>
#include <MCTS/Statistics/Recorder.hpp>

#include <sstream>

namespace RosettaTorch::MCTS
{
//!
//! \brief Statistics class.
//!
//! This class stores statistics data related to MCTS.
//! It enables only when 'ENABLE_STATISTICS' is set to true.
//!
template <bool enabled = ENABLE_STATISTICS>
class Statistics
{
 public:
    //! Writes statistics data that action is succeeded.
    //! \param isSimulation The flag indicates whether it is simulation mode.
    void ApplyActionSucceeded([[maybe_unused]] bool isSimulation)
    {
        // Do nothing
    }

    //! Returns debug message related to statistics data.
    void GetDebugMessage()
    {
        // Do nothing
    }
};

//!
//! \brief Statistics<true> class.
//!
//! This class is specialized class when 'ENABLE_STATISTICS' is true.
//!
template <>
class Statistics<true>
{
 public:
    //! Reports that iteration is succeed.
    void IterateSucceeded()
    {
        m_iter.ReportSuccess();
    }

    //! Reports that iteration is fail.
    void IterateFailed()
    {
        m_iter.ReportFail();
    }

    //! Returns the success count of iteration.
    //! \return The success count of iteration.
    int GetSuccededIterates() const
    {
        return m_iter.GetSuccessCount();
    }

    //! Writes statistics data that action is succeeded.
    //! \param isSimulation The flag indicates whether it is simulation mode.
    void ApplyActionSucceeded(bool isSimulation)
    {
        if (isSimulation)
        {
            return m_simulation.ReportSuccess();
        }
        else
        {
            return m_selection.ReportSuccess();
        }
    }

    //! Reports that selection action is succeed.
    void ApplySelectionActionSucceeded()
    {
        m_selection.ReportSuccess();
    }

    //! Reports that simulation action is succeed.
    void ApplySimulationActionSucceeded()
    {
        m_simulation.ReportSuccess();
    }

    //! Returns debug message related to statistics data.
    std::string GetDebugMessage() const
    {
        std::stringstream ss;

        ss << "Apply selection action success rate: ";
        PrintRate(ss, m_selection);
        ss << std::endl;

        ss << "Apply simulation action success rate: ";
        PrintRate(ss, m_simulation);
        ss << std::endl;

        ss << "Iterate success rate: ";
        PrintRate(ss, m_iter);
        ss << std::endl;

        return ss.str();
    }

 private:
    //! Prints success/total count and success rate.
    //! \p ss The string stream.
    //! \p rate The success rate recorder object.
    void PrintRate(std::stringstream& ss, const SuccessRateRecorder& rate) const
    {
        ss << rate.GetSuccessCount() << " / " << rate.GetTotalCount() << " ("
           << 100.0 * rate.GetSuccessRate() << "%)";
    }

    SuccessRateRecorder m_iter;
    SuccessRateRecorder m_selection;
    SuccessRateRecorder m_simulation;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_STATISTICS_HPP