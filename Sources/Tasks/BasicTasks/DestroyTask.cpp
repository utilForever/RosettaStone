/*************************************************************************
> File Name: DestroyTask.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim, SeungHyun Jeon
> Purpose: Implement DestroyTask
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim, SeungHyun Jeon
*************************************************************************/
#include <Tasks/BasicTasks/DestroyTask.h>
#include <Tasks/BasicTasks/DestroyWeaponTask.h>
#include <Tasks/BasicTasks/DestroyMinionTask.h>

namespace Hearthstonepp::BasicTasks
{
DestroyTask::DestroyTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

TaskID DestroyTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyTask::Impl(Player& player1, Player& player2)
{
    switch (m_entityType)
    {
        case EntityType::SOURCE:
            return DestroyMinionTask(source).Run(player1, player2);

        case EntityType::TARGET:
            return DestroyMinionTask(target).Run(player2, player1);

        case EntityType::OPPONENT_WEAPON:
            return DestroyWeaponTask().Run(player2, player1);

        default:
            return MetaData::INVALID;
    }
}
}  // namespace Hearthstonepp::BasicTasks