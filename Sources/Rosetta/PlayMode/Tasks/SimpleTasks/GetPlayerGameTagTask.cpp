// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetPlayerGameTagTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
GetPlayerGameTagTask::GetPlayerGameTagTask(GameTag tag) : m_gameTag(tag)
{
    // Do nothing
}

TaskStatus GetPlayerGameTagTask::Impl(Player* player)
{
    player->game->taskStack.num[0] = player->GetGameTag(m_gameTag);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> GetPlayerGameTagTask::CloneImpl()
{
    return std::make_unique<GetPlayerGameTagTask>(m_gameTag);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
