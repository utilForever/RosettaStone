// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_COUNT_TASK_HPP
#define ROSETTASTONE_COUNT_TASK_HPP

#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief CountTask class.
//!
//! This class represents the task for counting entities.
//!
class CountTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p numIndex.
    //! \param entityType The type of entity.
    //! \param numIndex An index of number.
    CountTask(EntityType entityType, int numIndex = 0);
    
    //! Constructs task with given \p entityType, \p numIndex and \p conditions.
    //! \param entityType The type of entity.
    //! \param numIndex An index of number.
    //! \param conditions SelfConditions to check.
    CountTask(EntityType entityType, std::vector<SelfCondition> conditions, int numIndex = 0);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    ITask* CloneImpl() override;

    std::vector<SelfCondition> m_conditions;
    int m_numIndex = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_COUNT_TASK_HPP
