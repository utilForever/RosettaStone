// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathSubtractTask.hpp>

namespace RosettaStone::SimpleTasks
{
MathSubtractTask::MathSubtractTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus MathSubtractTask::Impl(Player* player)
{
    player->game->taskStack.num[0] -= m_amount;

    return TaskStatus::COMPLETE;
}

ITask* MathSubtractTask::CloneImpl()
{
    return new MathSubtractTask(m_amount);
}
}  // namespace RosettaStone::SimpleTasks
