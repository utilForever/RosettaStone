// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_MULLIGAN_TASK_H
#define HEARTHSTONEPP_MULLIGAN_TASK_H

#include <hspp/Tasks/Requirement.h>
#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
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
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_MULLIGAN_TASK_H
