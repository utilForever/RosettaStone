// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_FREEZE_TASK_H
#define HEARTHSTONEPP_FREEZE_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
//!
//! \brief FreezeTask class.
//!
//! This class represents the task for freezing target.
//!
class FreezeTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p turn.
    //! \param entityType The entity type of target to freeze.
    //! \param turn The number of turns remaining until freeze is melted.
    FreezeTask(EntityType entityType, int turn);

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
    int m_turn;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_FREEZE_TASK_H
