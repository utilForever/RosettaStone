// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_HEAL_TASK_HPP
#define HEARTHSTONEPP_HEAL_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief HealTask class.
//!
//! This class represents the task for healing target.
//!
class HealTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p amount.
    //! \param entityType The entity type of target to heal.
    //! \param amount A value that indicates how much heal to target.
    HealTask(EntityType entityType, int amount);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    int m_amount = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // HEARTHSTONEPP_HEAL_TASK_HPP