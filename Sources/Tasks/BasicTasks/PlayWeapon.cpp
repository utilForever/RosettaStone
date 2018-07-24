/*************************************************************************
> File Name: PlayWeapon.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement PlayWeapon
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/PlayWeapon.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
PlayWeaponTask::PlayWeaponTask(Entity* entity) : m_entity(entity)
{
    // Do Nothing
}

TaskID PlayWeaponTask::GetTaskID() const
{
    return TaskID::PLAY_WEAPON;
}

MetaData PlayWeaponTask::Impl(Player& player1, Player&) const
{
    player1.hero->weapon = dynamic_cast<Weapon*>(m_entity);

    if (player1.hero->weapon == nullptr)
    {
        return MetaData::PLAY_WEAPON_DYNAMIC_CAST_FAIL;
    }

    return MetaData::PLAY_WEAPON_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks