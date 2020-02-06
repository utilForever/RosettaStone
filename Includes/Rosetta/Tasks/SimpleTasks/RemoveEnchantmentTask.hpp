// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_REMOVE_ENCHANTMENT_TASK_HPP
#define ROSETTASTONE_REMOVE_ENCHANTMENT_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RemoveEnchantmentTask class.
//!
//! This class represents the task for removing enchantment from entity.
//!
class RemoveEnchantmentTask : public ITask
{
 public:
    //! Default constructor.
    RemoveEnchantmentTask() = default;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_REMOVE_ENCHANTMENT_TASK_HPP
