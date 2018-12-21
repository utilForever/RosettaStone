// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_PLAY_WEAPON_TASK_HPP
#define HEARTHSTONEPP_PLAY_WEAPON_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::PlayerTasks
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
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    Entity* m_entity = nullptr;
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_PLAY_WEAPON_TASK_HPP
