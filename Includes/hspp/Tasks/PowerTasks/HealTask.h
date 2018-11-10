// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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

    EntityType m_entityType = EntityType::EMPTY;
    int m_amount = 0;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_HEAL_TASK_H