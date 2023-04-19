// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/CustomTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
CustomTask::CustomTask(std::function<void(Player*, Entity*, Playable*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

TaskStatus CustomTask::Impl(Player* player)
{
    m_func(player, m_source, m_target);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> CustomTask::CloneImpl()
{
    return std::make_unique<CustomTask>(m_func);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
