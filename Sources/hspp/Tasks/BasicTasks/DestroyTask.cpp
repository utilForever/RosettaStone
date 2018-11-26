// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/DestroyMinionTask.hpp>
#include <hspp/Tasks/BasicTasks/DestroyTask.hpp>
#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.hpp>

namespace Hearthstonepp::BasicTasks
{
DestroyTask::DestroyTask(EntityType entityType, Entity* source, Entity* target)
    : ITask(source, target), m_entityType(entityType)
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
            return DestroyMinionTask(m_source).Run(player);
        case EntityType::TARGET:
            return DestroyMinionTask(m_target).Run(player);
        case EntityType::ENEMY_WEAPON:
            return DestroyWeaponTask().Run(player.GetOpponent());
        default:
            return MetaData::INVALID;
    }
}
}  // namespace Hearthstonepp::BasicTasks