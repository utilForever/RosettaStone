#ifndef HEARTHSTONEPP_COMBAT_H
#define HEARTHSTONEPP_COMBAT_H

#include <Flatbuffers/generated/FlatData_generated.h>
#include <Tasks/Requirement.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief CombatTask class.
//!
//! This class represents the task for combating between two characters.
//!
class CombatTask : public ITask
{
 public:
    //! Constructs task with given \p agent.
    //! \param agent The task agent that is required to the requirement.
    CombatTask(TaskAgent& agent);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    Requirement m_requirement;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_COMBAT_H
