// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/EnqueueTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
EnqueueTask::EnqueueTask(std::vector<ITask*> tasks, int num, bool isSpellDamage)
    : m_tasks(std::move(tasks)), m_num(num), m_isSpellDamage(isSpellDamage)
{
    // Do nothing
}

TaskStatus EnqueueTask::Impl(Player* player)
{
    const int times =
        m_isSpellDamage ? m_num + player->currentSpellPower : m_num;

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

ITask* EnqueueTask::CloneImpl()
{
    return new EnqueueTask(m_tasks, m_num, m_isSpellDamage);
}
}  // namespace RosettaStone::SimpleTasks
