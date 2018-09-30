#ifndef HEARTHSTONEPP_MODIFY_HEALTH_TASK_H
#define HEARTHSTONEPP_MODIFY_HEALTH_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief ModifyHealthTask class.
//!
//! This class represents the task for modifying health of character.
//!
class ModifyHealthTask : public ITask
{
 public:
    //! Constructs task with given \p character and \p damage.
    //! \param character A pointer to character to modify the health.
    //! \param damage A value indicating how much to modify health.
    ModifyHealthTask(Character* character, BYTE damage);

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
    BYTE m_damage;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_MODIFYHEALTH_H
