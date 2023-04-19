// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathMultiplyTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
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
}  // namespace RosettaStone::PlayMode::SimpleTasks
