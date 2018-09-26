#ifndef HEARTHSTONEPP_BRIEF_H
#define HEARTHSTONEPP_BRIEF_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief BriefTask class.
//!
//! This class represents the task for briefing game status.
//! NOTE: The task agent sends game status to the game interface immediately
//! when brief task is run.
//!
class BriefTask : public ITask
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

#endif  // HEARTHSTONEPP_BRIEF_H
