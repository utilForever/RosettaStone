#ifndef HEARTHSTONEPP_POISONOUS_TASK_H
#define HEARTHSTONEPP_POISONOUS_TASK_H

#include <Tasks/Tasks.h>

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
    //! Constructs task with given \p source and \p target.
    //! \param source A pointer to attacking character.
    //! \param target A pointer to attacked character.
    PoisonousTask(Character* source, Character* target);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    Character* m_source;
    Character* m_target;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_POISONOUS_TASK_H
