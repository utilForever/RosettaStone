// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_EDGE_ADDON_HPP
#define ROSETTASTONE_TORCH_MCTS_EDGE_ADDON_HPP

#include <MCTS/Configs.hpp>

#include <atomic>
#include <cassert>
#include <cstdint>

namespace RosettaTorch::MCTS
{
//!
//! \brief EdgeAddon class.
//!
class EdgeAddon
{
 public:
    EdgeAddon() : m_chosenTimes(0), m_credit(0), m_total(0)
    {
        // Do nothing
    }

    void AddChosenTimes(int v)
    {
        m_chosenTimes += v;
    }

    auto GetChosenTimes() const
    {
        return m_chosenTimes.load();
    }

    float GetAverageCredit() const
    {
        const auto totalLoad = m_total.load();
        assert(totalLoad > 0);

        const float ret = static_cast<float>(m_credit.load()) / totalLoad;
        assert(ret >= -1.0);
        assert(ret <= 1.0);

        return ret;
    }

    void AddCredit(float score, int repeat_times = 1)
    {
        const int totalIncrement = CREDIT_GRANULARITY;
        const int creditIncrement =
            static_cast<int>(score * CREDIT_GRANULARITY);

        assert(creditIncrement >= -totalIncrement);
        assert(creditIncrement <= totalIncrement);

        // These two fields are not updated in an atomic operation. But this
        // should be fine...
        m_total += totalIncrement * repeat_times;
        m_credit += creditIncrement * repeat_times;
    }

    auto GetTotal() const
    {
        return m_total.load();
    }

 private:
    std::atomic<std::int64_t> m_chosenTimes;
    std::atomic<std::int64_t> m_credit;
    std::atomic<std::int64_t> m_total;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_EDGE_ADDON_HPP