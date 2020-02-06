// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
DiscardTask::DiscardTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus DiscardTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        player->game->taskQueue.StartEvent();

        player->GetHandZone()->Remove(playable);
        player->GetGraveyardZone()->Add(playable);

        player->game->ProcessTasks();
        player->game->taskQueue.EndEvent();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscardTask::CloneImpl()
{
    return std::make_unique<DiscardTask>(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
