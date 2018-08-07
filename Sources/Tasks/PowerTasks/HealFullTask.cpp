/*************************************************************************
> File Name: DestroyWeapon.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement DestroyWeapon
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/PowerTasks/HealFullTask.h>

namespace Hearthstonepp::PowerTask
{
HealFullTask::HealFullTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

MetaData HealFullTask::Impl(Player&, Player&)
{
    target->health = target->maxHealth;

    return MetaData::INVALID;
}
}  // namespace Hearthstonepp::PowerTask