// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/DestroyMinionTask.h>
#include <hspp/Tasks/BasicTasks/DestroyTask.h>
#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.h>

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
        case EntityType::ENEMY_WEAPON:
            return DestroyWeaponTask().Run(player2, player1);
        default:
            return MetaData::INVALID;
    }
}
}  // namespace Hearthstonepp::BasicTasks