#ifndef HEARTHSTONEPP_DESTROY_WEAPON_TASK_H
#define HEARTHSTONEPP_DESTROY_WEAPON_TASK_H

#include <hspp/Cards/Hero.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief DestroyWeaponTask class.
//!
//! This class represents the task for destroying weapon.
//!
class DestroyWeaponTask : public ITask
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

#endif  // HEARTHSTONEPP_DESTROY_WEAPON_TASK_H
