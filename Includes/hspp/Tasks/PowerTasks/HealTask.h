#ifndef HEARTHSTONEPP_HEAL_TASK_H
#define HEARTHSTONEPP_HEAL_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
//!
//! \brief HealTask class.
//!
//! This class represents the task for healing target.
//!
class HealTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p amount.
    //! \param entityType The entity type of target to heal.
    //! \param amount A value that indicates how much heal to target.
    HealTask(EntityType entityType, int amount);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player&) override;

    EntityType m_entityType;
    int m_amount;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_HEALTASK_H