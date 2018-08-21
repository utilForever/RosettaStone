/*************************************************************************
> File Name: DestroyWeapon.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement DestroyWeapon
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/DestroyTask.h>

namespace Hearthstonepp::BasicTask
{
DestroyTask::DestroyTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

TaskID DestroyTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyTask::Impl(Player&, Player& player2)
{
    if (m_entityType == +EntityType::OPPONENT_WEAPON)
    {
        player2.hero->weapon = nullptr;
        return MetaData::DESTROY_OPPONENT_WEAPON_SUCCESS;
    }

    return MetaData::INVALID;
}
}  // namespace Hearthstonepp::PowerTask