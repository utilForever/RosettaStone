// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/DestroyMinionTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyWeaponTask.hpp>

namespace Hearthstonepp::SimpleTasks
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

TaskStatus DestroyTask::Impl(Player& player)
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
            return TaskStatus::INVALID;
    }
}
}  // namespace Hearthstonepp::SimpleTasks