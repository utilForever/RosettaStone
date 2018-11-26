// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_END_TASK_HPP
#define HEARTHSTONEPP_GAME_END_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief GameEndTask class.
//!
//! This class represents the task for telling the game is over.
//!
class GameEndTask : public ITask
{
 public:
    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_GAME_END_TASK_HPP
