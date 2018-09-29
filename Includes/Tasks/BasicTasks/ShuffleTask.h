#ifndef HEARTHSTONEPP_SHUFFLE_H
#define HEARTHSTONEPP_SHUFFLE_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief ShuffleTask class.
//!
//! This class represents the task for shuffling cards in deck.
//!
class ShuffleTask : public ITask
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

#endif  // HEARTHSTONEPP_SHUFFLE_H
