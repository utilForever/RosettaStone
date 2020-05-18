// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/EnqueueNumberTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
EnqueueNumberTask::EnqueueNumberTask(std::vector<std::shared_ptr<ITask>> tasks,
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

    const int times =
        m_isSpellDamage ? num + player->GetCurrentSpellPower() : num;

    for (int i = 0; i < times; ++i)
    {
        for (auto& task : m_tasks)
        {
            std::unique_ptr<ITask> clonedTask = task->Clone();

            clonedTask->SetPlayer(player);
            clonedTask->SetSource(m_source);
            clonedTask->SetTarget(m_target);

            player->game->taskQueue.Enqueue(std::move(clonedTask));
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> EnqueueNumberTask::CloneImpl()
{
    return std::make_unique<EnqueueNumberTask>(m_tasks, m_isSpellDamage);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
