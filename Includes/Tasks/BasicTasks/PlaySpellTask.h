#ifndef HEARTHSTONEPP_PLAYSPELL_H
#define HEARTHSTONEPP_PLAYSPELL_H

#include <Tasks/Requirement.h>
#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief PlaySpellTask class.
//!
//! This class represents the task for playing spell.
//! It specifies target and casts spell to given target.
//!
class PlaySpellTask : public ITask
{
 public:
    //! Constructs task with given \p agent and \p entity.
    //! \param agent The task agent that interacts with game interface.
    //! \param entity A pointer to spell to cast.
    PlaySpellTask(TaskAgent& agent, Entity* entity);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    Entity* m_entity;
    Requirement m_requirement;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAYSPELL_H
