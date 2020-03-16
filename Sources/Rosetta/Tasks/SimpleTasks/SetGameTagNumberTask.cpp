// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagNumberTask.hpp>

namespace RosettaStone::SimpleTasks
{
SetGameTagNumberTask::SetGameTagNumberTask(EntityType entityType, GameTag tag)
    : ITask(entityType), m_gameTag(tag)
{
    // Do nothing
}

TaskStatus SetGameTagNumberTask::Impl(Player* player)
{
    auto playables =
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
}  // namespace RosettaStone::SimpleTasks
