// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_INCLUDE_TASK_HPP
#define HEARTHSTONEPP_INCLUDE_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

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

    //! Returns a list of entities based on the type of entity.
    //! \param entityType The type of entity.
    //! \param player The player to get hand or battlefield.
    //! \param source The source that indicates source entity.
    //! \param target The target that indicates target entity.
    //! \return A list of entities based on the type of entity.
    static std::vector<Entity*> GetEntities(EntityType entityType,
                                            Player& player,
                                            Entity* source = nullptr,
                                            Entity* target = nullptr);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;
};
}  // namespace Hearthstonepp::SimpleTasks

#endif  // HEARTHSTONEPP_INCLUDE_TASK_HPP
