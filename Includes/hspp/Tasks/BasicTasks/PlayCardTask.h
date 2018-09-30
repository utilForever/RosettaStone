#ifndef HEARTHSTONEPP_PLAY_CARD_TASK_H
#define HEARTHSTONEPP_PLAY_CARD_TASK_H

#include <hspp/Tasks/Requirement.h>
#include <hspp/Tasks/Tasks.h>

#include <hspp/Flatbuffers/generated/FlatData_generated.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief PlayCardTask class.
//!
//! This class represents the task for playing card from hand.
//! Then it runs each task according to the card type.
//!
class PlayCardTask : public ITask
{
 public:
    //! Constructs task with given \p agent.
    //! \param agent The task agent that performs card play.
    PlayCardTask(TaskAgent& agent);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    TaskAgent& m_agent;
    Requirement m_requirement;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAYCARD_H
