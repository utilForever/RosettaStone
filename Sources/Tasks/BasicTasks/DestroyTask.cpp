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
            return DestroyMinionTask(player1, source).Run(player1, player2);

        case EntityType::TARGET:
            return DestroyMinionTask(player2, target).Run(player1, player2);

        case EntityType::OPPONENT_WEAPON:
            return DestroyWeaponTask(player2.hero).Run(player1, player2);

        default:
            return MetaData::INVALID;
    }
}
}  // namespace Hearthstonepp::BasicTasks