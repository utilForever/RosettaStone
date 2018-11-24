// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_DESTROY_TASK_H
#define HEARTHSTONEPP_DESTROY_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief DestroyTask class.
//!
//! This class represents the task for destroying something such as minion.
//!
class DestroyTask : public ITask
{
 public:
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type of target to destroy.
    //! \param source A pointer to source character to destroy.
    //! \param target A pointer to target character to destroy.
    DestroyTask(EntityType entityType, Entity* source = nullptr,
                Entity* target = nullptr);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    EntityType m_entityType = EntityType::EMPTY;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_DESTROY_TASK_H
