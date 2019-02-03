// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_MULLIGAN_TASK_HPP
#define HEARTHSTONEPP_MULLIGAN_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::PlayerTasks
{
//!
//! \brief MulliganTask class.
//!
//! This class represents the task for performing mulligan.
//!
class MulliganTask : public ITask
{
 public:
    //! Default constructor.
    MulliganTask() = default;

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

#endif  // HEARTHSTONEPP_MULLIGAN_TASK_HPP
