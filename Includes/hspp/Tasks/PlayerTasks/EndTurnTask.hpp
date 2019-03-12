// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_END_TURN_TASK_HPP
#define HEARTHSTONEPP_END_TURN_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::PlayerTasks
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
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_END_TURN_TASK_HPP
