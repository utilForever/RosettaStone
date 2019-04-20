// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_MANA_CRYSTAL_TASK_HPP
#define ROSETTASTONE_MANA_CRYSTAL_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief ManaCrystalTask class.
//!
//! This class represents the task for changing mana crystal of player.
//!
class ManaCrystalTask : public ITask
{
 public:
    //! Constructs task with given \p amount and \p fill.
    //! \param amount A value indicating how much to change mana crystal.
    //! \param fill true if mana crystal is filled, and false otherwise.
    explicit ManaCrystalTask(int amount, bool fill);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    int m_amount;
    bool m_fill;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_MANA_CRYSTAL_TASK_HPP
