// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_FILTER_STACK_TASK_HPP
#define ROSETTASTONE_PLAYMODE_FILTER_STACK_TASK_HPP

#include <Rosetta/PlayMode/Conditions/RelaCondition.hpp>
#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
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
    //! Constructs task with given \p selfConditions.
    //! \param selfConditions A list of self conditions to filter.
    explicit FilterStackTask(
        std::vector<std::shared_ptr<SelfCondition>> selfConditions);

    //! Constructs task with given \p type and \p relaConditions.
    //! \param type The entity type of target to filter.
    //! \param relaConditions A list of relation conditions to filter.
    explicit FilterStackTask(
        EntityType type,
        std::vector<std::shared_ptr<RelaCondition>> relaConditions);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::vector<std::shared_ptr<SelfCondition>> m_selfConditions;
    std::vector<std::shared_ptr<RelaCondition>> m_relaConditions;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_FILTER_STACK_TASK_HPP
