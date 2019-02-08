// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/PlayerTasks/PlayWeaponTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
PlayWeaponTask::PlayWeaponTask(Entity* entity) : m_entity(entity)
{
    // Do nothing
}

TaskID PlayWeaponTask::GetTaskID() const
{
    return TaskID::PLAY_WEAPON;
}

TaskStatus PlayWeaponTask::Impl(Player& player)
{
    player.GetHero()->weapon = dynamic_cast<Weapon*>(m_entity);

    if (player.GetHero()->weapon == nullptr)
    {
        return TaskStatus::PLAY_WEAPON_DYNAMIC_CAST_FAIL;
    }

    return TaskStatus::PLAY_WEAPON_SUCCESS;
}
}  // namespace Hearthstonepp::PlayerTasks