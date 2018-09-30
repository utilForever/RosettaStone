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
    //! \param entityType The type of entity to destroy.
    DestroyTask(EntityType entityType);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    EntityType m_entityType;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_DESTROY_TASK_H
