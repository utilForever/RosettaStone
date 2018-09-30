#ifndef HEARTHSTONEPP_HEAL_FULL_TASK_H
#define HEARTHSTONEPP_HEAL_FULL_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
//!
//! \brief HealFullTask class.
//!
//! This class represents the task for healing target fully.
//!
class HealFullTask : public ITask
{
 public:
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type of target to heal.
    HealFullTask(EntityType entityType);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    EntityType m_entityType;

    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_HEAL_FULL_TASK_H
