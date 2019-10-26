// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_FILTER_STACK_TASK_HPP
#define ROSETTASTONE_FILTER_STACK_TASK_HPP

#include <Rosetta/Conditions/RelaCondition.hpp>
#include <Rosetta/Conditions/SelfCondition.hpp>
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
    //! Constructs task with given \p selfCondition.
    //! \param selfCondition A self condition to filter.
    explicit FilterStackTask(SelfCondition selfCondition);

    //! Constructs task with given \p type and \p relaCondition.
    //! \param type The entity type of target to filter.
    //! \param relaCondition A relation condition to filter.
    FilterStackTask(EntityType type, RelaCondition relaCondition);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    SelfCondition* m_selfCondition = nullptr;
    RelaCondition* m_relaCondition = nullptr;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_FILTER_STACK_TASK_HPP
