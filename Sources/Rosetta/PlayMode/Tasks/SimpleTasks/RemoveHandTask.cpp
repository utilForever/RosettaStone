// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RemoveHandTask.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
RemoveHandTask::RemoveHandTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus RemoveHandTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    std::vector<Playable*> list;

    for (auto& playable : playables)
    {
        if (playable->zone->GetType() == ZoneType::HAND)
        {
            playable->player->GetHandZone()->Remove(playable);
            list.emplace_back(playable);
        }
    }

    player->game->taskStack.playables = list;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RemoveHandTask::CloneImpl()
{
    return std::make_unique<RemoveHandTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
