// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_GET_EVENT_NUMBER_TASK_HPP
#define ROSETTASTONE_PLAYMODE_GET_EVENT_NUMBER_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief GetEventNumberTask class.
//!
//! This class represents the task for getting number of the current event and
//! stores it to the stack. (e.g. the amount damage dealt or heal taken)
//!
class GetEventNumberTask : public ITask
{
 public:
    //! Constructs task with given \p numIndex.
    //! \param numIndex An index of number.
    GetEventNumberTask(int numIndex = 0);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_numIndex = 0;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_GET_EVENT_NUMBER_TASK_HPP
