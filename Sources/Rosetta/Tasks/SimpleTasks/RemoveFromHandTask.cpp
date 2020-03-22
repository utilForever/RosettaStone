// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveFromHandTask.hpp>

namespace RosettaStone::SimpleTasks
{
RemoveFromHandTask::RemoveFromHandTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskStatus RemoveFromHandTask::Impl(Player* player)
{
    std::vector<Playable*> result;

    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    for (auto& entity : entities)
    {
        if (entity->GetZoneType() == ZoneType::HAND)
        {
            entity->zone->Remove(entity);
            result.emplace_back(entity);
        }
    }

    player->game->taskStack.playables = result;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RemoveFromHandTask::CloneImpl()
{
    return std::make_unique<RemoveFromHandTask>(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
