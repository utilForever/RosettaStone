// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_EDGE_ADDON_HPP
#define ROSETTASTONE_TORCH_MCTS_EDGE_ADDON_HPP

#include <atomic>
#include <cstdint>

namespace RosettaTorch::MCTS
{
//!
//! \brief EdgeAddon class.
//!
//! This class is addon class that includes utility methods for edge.
//!
class EdgeAddon
{
 public:
    //! Constructs edge addon by initializing variables.
    EdgeAddon();

    //! Adds \p val to chosen times of the edge.
    //! \param val The value to add to chosen times of the edge.
    void AddChosenTimes(int val);

    //! Returns chosen times of the edge.
    //! \return Chosen times of the edge.
    std::int64_t GetChosenTimes() const;

    //! Returns average credit of the edge.
    //! \return Average credit of the edge.
    float GetAverageCredit() const;

    //! Adds \p score to credit of the edge.
    //! \param score The value to add to credit of the edge.
    //! \param repeatTimes The value to indicate how many times you want to add.
    void AddCredit(float score, int repeatTimes = 1);

    //! Returns total credit of the edge.
    //! \return Total credit of the edge.
    std::int64_t GetTotal() const;

 private:
    std::atomic<std::int64_t> m_chosenTimes;
    std::atomic<std::int64_t> m_credit;
    std::atomic<std::int64_t> m_total;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_EDGE_ADDON_HPP