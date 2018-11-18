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

MetaData DestroyTask::Impl(Player& player)
{
    switch (m_entityType)
    {
        case EntityType::SOURCE:
            return DestroyMinionTask(source).Run(player);
        case EntityType::TARGET:
            return DestroyMinionTask(target).Run(player);
        case EntityType::ENEMY_WEAPON:
            return DestroyWeaponTask().Run(player.GetOpponent());
        default:
            return MetaData::INVALID;
    }
}
}  // namespace Hearthstonepp::BasicTasks