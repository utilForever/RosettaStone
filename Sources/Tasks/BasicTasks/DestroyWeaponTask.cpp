/*************************************************************************
> File Name: DestroyWeaponTask.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement DestroyWeapon
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/DestroyWeaponTask.h>

namespace Hearthstonepp::BasicTasks
{
DestroyWeaponTask::DestroyWeaponTask(Hero* hero) : m_hero(hero)
{
    // Do nothing
}

TaskID DestroyWeaponTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyWeaponTask::Impl(Player &, Player &)
{
    m_hero->weapon = nullptr;
    return MetaData::DESTROY_OPPONENT_WEAPON_SUCCESS;

}
}
