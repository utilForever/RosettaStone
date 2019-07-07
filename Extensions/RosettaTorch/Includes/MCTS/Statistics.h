// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_STATISTICS_HPP
#define ROSETTASTONE_TORCH_MCTS_STATISTICS_HPP

#include <MCTS/Configs.hpp>

#include <atomic>
#include <sstream>

namespace RosettaTorch::MCTS
{
template <bool enabled = ENABLE_STATISTICS>
class Statistics
{
 public:
    void ApplyActionSucceeded([[maybe_unused]] bool isSimulation)
    {
        // Do nothing
    }

    void GetDebugMessage()
    {
        // Do nothing
    }
};

class SuccessRateRecorder
{
 public:
    SuccessRateRecorder() : m_success(0), m_total(0)
    {
        // Do nothing
    }

    void ReportSuccess()
    {
        ++m_success;
        ++m_total;
    }

    void ReportFailed()
    {
        ++m_total;
    }

    int GetSuccessCount() const
    {
        return m_success;
    }

    int GetTotalCount() const
    {
        return m_total;
    }

    double GetSuccessRate() const
    {
        if (m_total == 0)
        {
            return 0.0;
        }

        return static_cast<double>(m_success) / m_total;
    }

 private:
    std::atomic<int> m_success;
    std::atomic<int> m_total;
};

template <>
class Statistics<true>
{
 public:
    void IterateSucceeded()
    {
        m_iter.ReportSuccess();
    }

    void IterateFailed()
    {
        m_iter.ReportFailed();
    }

    auto GetSuccededIterates() const
    {
        return m_iter.GetSuccessCount();
    }

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

    void ApplySelectionActionSucceeded()
    {
        m_selection.ReportSuccess();
    }

    void ApplySimulationActionSucceeded()
    {
        m_simulation.ReportSuccess();
    }

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