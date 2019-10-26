// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

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
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        player.GetGame()->taskQueue.StartEvent();

        player.GetHandZone().Remove(*entity);
        player.GetGraveyardZone().Add(*entity);

        player.GetGame()->ProcessTasks();
        player.GetGame()->taskQueue.EndEvent();
    }

    return TaskStatus::COMPLETE;
}

ITask* DiscardTask::CloneImpl()
{
    return new DiscardTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
