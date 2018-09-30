#ifndef HEARTHSTONEPP_SWAP_PLAYER_TASK_H
#define HEARTHSTONEPP_SWAP_PLAYER_TASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief SwapPlayerTask class.
//!
//! This class represents the task for swapping two players.
//!
class SwapPlayerTask : public ITask
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

#endif  // HEARTHSTONEPP_SWAPPLAYER_H
