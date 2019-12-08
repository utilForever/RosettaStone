// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_CONDITION_TASK_HPP
#define ROSETTASTONE_CONDITION_TASK_HPP

#include <Rosetta/Conditions/RelaCondition.hpp>
#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
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
    explicit ConditionTask(EntityType entityType,
                           std::vector<SelfCondition*> selfConditions);

    //! Constructs task with given \p entityType and \p relaConditions.
    //! \param entityType The entity type to check condition.
    //! \param relaConditions A container of relation condition.
    explicit ConditionTask(EntityType entityType,
                           std::vector<RelaCondition*> relaConditions);

    //! Constructs task with given \p entityType and \p selfConditions and \p relaConditions.
    //! \param entityType The entity type to check condition.
    //! \param selfConditions A container of self condition.
    //! \param relaConditions A container of relation condition.
    explicit ConditionTask(EntityType entityType,
                           std::vector<SelfCondition*> selfConditions,
                           std::vector<RelaCondition*> relaConditions);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    std::vector<SelfCondition*> m_selfConditions;
    std::vector<RelaCondition*> m_relaConditions;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_CONDITION_TASK_HPP
