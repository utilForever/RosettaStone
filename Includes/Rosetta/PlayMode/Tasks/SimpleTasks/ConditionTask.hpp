// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CONDITION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_CONDITION_TASK_HPP

#include <Rosetta/PlayMode/Conditions/RelaCondition.hpp>
#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief ConditionTask class.
//!
//! This class represents the task for checking condition.
//!
class ConditionTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p selfConditions.
    //! \param entityType The entity type to check condition.
    //! \param selfConditions A container of self condition.
    explicit ConditionTask(
        EntityType entityType,
        std::vector<std::shared_ptr<SelfCondition>> selfConditions);

    //! Constructs task with given \p entityType and \p relaConditions.
    //! \param entityType The entity type to check condition.
    //! \param relaConditions A container of relation condition.
    explicit ConditionTask(
        EntityType entityType,
        std::vector<std::shared_ptr<RelaCondition>> relaConditions);

    //! Constructs task with given \p entityType and \p selfConditions and \p
    //! relaConditions. \param entityType The entity type to check condition.
    //! \param selfConditions A container of self condition.
    //! \param relaConditions A container of relation condition.
    explicit ConditionTask(
        EntityType entityType,
        std::vector<std::shared_ptr<SelfCondition>> selfConditions,
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

#endif  // ROSETTASTONE_PLAYMODE_CONDITION_TASK_HPP
