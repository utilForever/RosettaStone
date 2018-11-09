// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H
#define HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H

#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief InitAttackCountTask class.
//!
//! This class represents the task for initializing attack count.
//!
class InitAttackCountTask : public ITask
{
 public:
    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    //! Processes attack count initialization logic of my field.
    //! \param my The player.
    void ProcessMyField(Player& my);

    //! Processes attack count initialization logic of enemy field.
    //! \param opponent The opponent player.
    void ProcessEnemyField(Player& opponent);
};

}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H
