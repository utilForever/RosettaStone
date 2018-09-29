#ifndef HEARTHSTONEPP_DISCARD_TASK_H
#define HEARTHSTONEPP_DISCARD_TASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
//!
//! \brief DiscardTask class.
//!
//! This class represents the task for discarding card(s) from hand.
//!
class DiscardTask : public ITask
{
 public:
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type of target to discard card(s).
    DiscardTask(EntityType entityType);

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
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_DISCARD_TASK_H