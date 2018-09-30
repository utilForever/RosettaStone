#ifndef HEARTHSTONEPP_DESTORY_MINION_TASK_H
#define HEARTHSTONEPP_DESTORY_MINION_TASK_H

#include <hspp/Cards/Character.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief DestroyMinionTask class.
//!
//! This class represents the task for destroying minion.
//!
class DestroyMinionTask : public ITask
{
 public:
    //! Constructs task with given \p character.
    //! \param character A pointer to character to destroy.
    DestroyMinionTask(Character* character);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    Character* m_character;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_DESTORY_MINION_TASK_H
