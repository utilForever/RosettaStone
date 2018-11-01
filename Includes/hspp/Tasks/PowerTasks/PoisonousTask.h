// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_POISONOUS_TASK_H
#define HEARTHSTONEPP_POISONOUS_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
//!
//! \brief PoisonousTask class.
//!
//! This class represents the task for dealing with poisonous ability in combat.
//!
class PoisonousTask : public ITask
{
 public:
    //! Constructs task with given \p target.
    //! \param target A pointer to attacked character.
    PoisonousTask(Character* target);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    Character* m_target;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_POISONOUS_TASK_H
