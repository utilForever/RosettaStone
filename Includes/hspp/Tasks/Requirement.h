// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_REQUIREMENT_H
#define HEARTHSTONEPP_REQUIREMENT_H

#include <hspp/Enums/TaskEnums.h>
#include <hspp/Tasks/TaskAgent.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief Requirement class.
//!
//! This class sends requirements to game interface and returns meta data that
//! the result of the task.
//!
class Requirement
{
 public:
    //! Constructs requirement with given \p request and \p agent.
    //! \param request A task ID to request.
    //! \param agent A task agent.
    Requirement(TaskID request, TaskAgent& agent);

    //! Notifies task meta to main channel reads task meta from side channel.
    //! \param userID The unique user ID.
    //! \param meta The meta data that the result of the task.
    void Interact(BYTE userID, TaskMeta& meta) const;

 private:
    TaskID m_request;
    TaskAgent& m_agent;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_REQUIREMENT_H