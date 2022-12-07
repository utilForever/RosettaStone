// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayLocationTask.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::PlayerTasks
{
PlayLocationTask::PlayLocationTask(Entity* source, Playable* target)
    : ITask(source, target)
{
    // Do nothing
}

TaskStatus PlayLocationTask::Impl(Player* player)
{
    const auto location = dynamic_cast<Location*>(m_source);

    if (!location)
    {
        throw std::invalid_argument("PlayLocationTask - It's not a location");
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> PlayLocationTask::CloneImpl()
{
    return std::make_unique<PlayLocationTask>(m_source, m_target);
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
