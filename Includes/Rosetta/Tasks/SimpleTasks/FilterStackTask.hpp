// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_FILTER_STACK_TASK_HPP
#define ROSETTASTONE_FILTER_STACK_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief FilterStackTask class.
//!
//! This class represents the task for storing entities to stack after
//! filtering them with self condition.
//!
class FilterStackTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p selfCondition.
    //! \param entityType The entity type of target to filter.
    //! \param selfCondition A self condition to filter.
    FilterStackTask(EntityType entityType, SelfCondition selfCondition);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    SelfCondition* m_selfCondition = nullptr;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_FILTER_STACK_TASK_HPP
