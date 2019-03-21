// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_END_TURN_TASK_HPP
#define ROSETTASTONE_END_TURN_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::PlayerTasks
{
//!
//! \brief EndTurnTask class.
//!
//! This class represents the task for ending current player's turn.
//!
class EndTurnTask : public ITask
{
 public:
    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;
};
}  // namespace RosettaStone::PlayerTasks

#endif  // ROSETTASTONE_END_TURN_TASK_HPP
