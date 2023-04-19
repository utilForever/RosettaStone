// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathAddTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
MathAddTask::MathAddTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus MathAddTask::Impl(Player* player)
{
    player->game->taskStack.num[0] += m_amount;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MathAddTask::CloneImpl()
{
    return std::make_unique<MathAddTask>(m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
