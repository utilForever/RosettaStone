// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_INCLUDE_TASK_HPP
#define HEARTHSTONEPP_INCLUDE_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::SimpleTasks
{
//!
//! \brief IncludeTask class.
//!
//! This class represents the task for including entities to be applied by
//! another task.
//!
class IncludeTask : public ITask
{
 public:
    //! Default constructor.
    IncludeTask() = default;

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

    static std::vector<Entity*> GetEntities(EntityType entityType,
                                            Player& player);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;
};
}  // namespace Hearthstonepp::SimpleTasks

#endif  // HEARTHSTONEPP_INCLUDE_TASK_HPP
