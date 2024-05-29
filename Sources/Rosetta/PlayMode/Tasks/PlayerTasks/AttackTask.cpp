// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2024 Chris Ohk

#include <Rosetta/PlayMode/Actions/Attack.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
AttackTask::AttackTask(Entity* source, Playable* target) : ITask(source, target)
{
    // Do nothing
}

TaskStatus AttackTask::Impl(Player* player)
{
    Generic::Attack(player, dynamic_cast<Character*>(m_source),
                    dynamic_cast<Character*>(m_target), false);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AttackTask::CloneImpl()
{
    return std::make_unique<AttackTask>(m_source, m_target);
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
