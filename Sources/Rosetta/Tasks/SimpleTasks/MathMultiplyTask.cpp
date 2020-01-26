// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathMultiplyTask.hpp>

namespace RosettaStone::SimpleTasks
{
MathMultiplyTask::MathMultiplyTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus MathMultiplyTask::Impl(Player* player)
{
    player->game->taskStack.num[0] *= m_amount;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MathMultiplyTask::CloneImpl()
{
    return std::make_unique<MathMultiplyTask>(m_amount);
}
}  // namespace RosettaStone::SimpleTasks
