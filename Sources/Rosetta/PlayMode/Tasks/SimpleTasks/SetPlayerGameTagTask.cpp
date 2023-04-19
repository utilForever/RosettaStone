// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetPlayerGameTagTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SetPlayerGameTagTask::SetPlayerGameTagTask(GameTag tag, int value)
    : m_gameTag(tag), m_value(value)
{
    // Do nothing
}

TaskStatus SetPlayerGameTagTask::Impl(Player* player)
{
    player->SetGameTag(m_gameTag, m_value);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SetPlayerGameTagTask::CloneImpl()
{
    return std::make_unique<SetPlayerGameTagTask>(m_gameTag, m_value);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
