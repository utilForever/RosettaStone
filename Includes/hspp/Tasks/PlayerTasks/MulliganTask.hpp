// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_MULLIGAN_TASK_HPP
#define HEARTHSTONEPP_MULLIGAN_TASK_HPP

#include <hspp/Tasks/Requirement.hpp>
#include <hspp/Tasks/TaskAgent.hpp>
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
    //! Constructs task with given \p agent.
    //! \param agent The task agent that performs card draw.
    MulliganTask(TaskAgent& agent);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    Requirement m_requirement;
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_MULLIGAN_TASK_HPP
