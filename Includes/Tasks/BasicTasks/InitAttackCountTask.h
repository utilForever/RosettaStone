#ifndef HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H
#define HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H

#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

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
};

}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H
