// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_PLAY_WEAPON_TASK_H
#define HEARTHSTONEPP_PLAY_WEAPON_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief PlayWeaponTask class.
//!
//! This class represents the task for playing weapon.
//! It equips the weapon to hero.
//!
class PlayWeaponTask : public ITask
{
 public:
    //! Constructs task with given \p entity.
    //! \param entity The weapon to equip.
    PlayWeaponTask(Entity* entity);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    Entity* m_entity = nullptr;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAY_WEAPON_TASK_H
