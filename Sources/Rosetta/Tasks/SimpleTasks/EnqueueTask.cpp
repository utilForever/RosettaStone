// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/EnqueueTask.hpp>

namespace RosettaStone::SimpleTasks
{
EnqueueTask::EnqueueTask(std::vector<ITask*> tasks, int num)
    : m_tasks(tasks), m_num(num)
{
    // Do nothing
}

TaskID EnqueueTask::GetTaskID() const
{
    return TaskID::ENQUEUE;
}

TaskStatus EnqueueTask::Impl(Player& player)
{
    for (int i = 0; i < m_num; ++i)
    {
        for (auto& task : m_tasks)
        {
            task->Run(player);
        }
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
