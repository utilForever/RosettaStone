// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Attack.hpp>
#include <hspp/Tasks/PlayerTasks/AttackTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
AttackTask::AttackTask(Entity* source, Entity* target) : ITask(source, target)
{
    // Do nothing
}

TaskID AttackTask::GetTaskID() const
{
    return TaskID::ATTACK;
}

TaskStatus AttackTask::Impl(Player& player)
{
    Generic::Attack(player, dynamic_cast<Character*>(m_source),
                    dynamic_cast<Character*>(m_target));

    return TaskStatus::COMPLETE;
}
}  // namespace Hearthstonepp::PlayerTasks
