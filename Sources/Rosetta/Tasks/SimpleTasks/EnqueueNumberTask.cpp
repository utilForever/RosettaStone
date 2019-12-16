// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/EnqueueNumberTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
EnqueueNumberTask::EnqueueNumberTask(std::vector<ITask*> tasks,
                                     bool isSpellDamage)
    : m_tasks(std::move(tasks)), m_isSpellDamage(isSpellDamage)
{
    // Do nothing
}

TaskStatus EnqueueNumberTask::Impl(Player* player)
{
    const int num = player->game->taskStack.num[0];
    if (num < 1)
    {
        return TaskStatus::STOP;
    }

    const int times = m_isSpellDamage ? num + player->currentSpellPower : num;

    for (int i = 0; i < times; ++i)
    {
        for (auto& task : m_tasks)
        {
            ITask* clonedTask = task->Clone();

            clonedTask->SetPlayer(player);
            clonedTask->SetSource(m_source);
            clonedTask->SetTarget(m_target);

            player->game->taskQueue.Enqueue(clonedTask);
        }
    }

    return TaskStatus::COMPLETE;
}

ITask* EnqueueNumberTask::CloneImpl()
{
    return new EnqueueNumberTask(m_tasks, m_isSpellDamage);
}
}  // namespace RosettaStone::SimpleTasks
