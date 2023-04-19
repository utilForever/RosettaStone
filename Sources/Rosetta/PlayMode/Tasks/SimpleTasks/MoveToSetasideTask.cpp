// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MoveToSetasideTask.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
MoveToSetasideTask::MoveToSetasideTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskStatus MoveToSetasideTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->zone->Remove(playable);
        playable->player->GetSetasideZone()->Add(playable);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MoveToSetasideTask::CloneImpl()
{
    return std::make_unique<MoveToSetasideTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
