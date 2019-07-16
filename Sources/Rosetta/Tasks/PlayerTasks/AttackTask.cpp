// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Attack.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>

namespace RosettaStone::PlayerTasks
{
AttackTask::AttackTask(Entity* source, Entity* target) : ITask(source, target)
{
    // Do nothing
}

TaskID AttackTask::GetTaskID() const
{
    return TaskID::ATTACK;
}

ITask* AttackTask::CloneImpl()
{
    return new AttackTask(m_source, m_target);
}

TaskStatus AttackTask::Impl(Player& player)
{
    Generic::Attack(player, dynamic_cast<Character*>(m_source),
                    dynamic_cast<Character*>(m_target));

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::PlayerTasks
