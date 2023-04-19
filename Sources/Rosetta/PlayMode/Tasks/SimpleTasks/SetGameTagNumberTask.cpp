// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetGameTagNumberTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SetGameTagNumberTask::SetGameTagNumberTask(EntityType entityType, GameTag tag)
    : ITask(entityType), m_gameTag(tag)
{
    // Do nothing
}

TaskStatus SetGameTagNumberTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->SetGameTag(m_gameTag, player->game->taskStack.num[0]);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SetGameTagNumberTask::CloneImpl()
{
    return std::make_unique<SetGameTagNumberTask>(m_entityType, m_gameTag);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
