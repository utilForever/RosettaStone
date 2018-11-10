// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_PLAYER_SETTING_TASK_H
#define HEARTHSTONEPP_PLAYER_SETTING_TASK_H

#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief PlayerSettingTask class.
//!
//! This class represents the task for setting player information.
//!
class PlayerSettingTask : public ITask
{
 public:
    //! Constructs task with given \p agent.
    //! \param agent The task agent that notifies the result of player setting.
    PlayerSettingTask(TaskAgent& agent);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    TaskAgent& m_agent;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAYER_SETTING_TASK_H
