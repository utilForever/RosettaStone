// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_NUMBER_CONDITION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_NUMBER_CONDITION_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief NumberConditionTask class.
//!
//! This class represents the task for comparing number in the task stack
//! and the given reference value.
//!
class NumberConditionTask : public ITask
{
 public:
    //! Constructs task with given \p referenceValue and \p relaSign.
    //! \param referenceValue The reference value to compare.
    //! \param relaSign The relation sign to compare.
    explicit NumberConditionTask(int referenceValue, RelaSign relaSign);

    //! Constructs task with given \p relaSign.
    //! \param relaSign The relation sign to compare.
    explicit NumberConditionTask(RelaSign relaSign);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_referenceValue = 0;
    RelaSign m_relaSign = RelaSign::EQ;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_NUMBER_CONDITION_TASK_HPP
