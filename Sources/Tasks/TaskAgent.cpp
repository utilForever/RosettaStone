/*************************************************************************
> File Name: TaskAgent.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Agent for managing Task Unit
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/TaskAgent.h>
#include <Tasks/TaskSerializer.h>

namespace Hearthstonepp
{
void TaskAgent::Read(TaskMeta& meta, bool sideChannel)
{
    if (sideChannel)
    {
        m_sideChannel.ReadBuffer(meta);
    }
    else
    {
        m_syncBuffer.ReadBuffer(meta);
    }
}

void TaskAgent::Notify(TaskMeta&& meta, bool sideChannel)
{
    if (sideChannel)
    {
        m_sideChannel.WriteBuffer(std::move(meta));
    }
    else
    {
        m_syncBuffer.WriteBuffer(std::move(meta));
    }
}

void TaskAgent::Run(TaskMeta& meta, Player& current, Player& opponent)
{
    Run(m_tasks, meta, current, opponent);
}

void TaskAgent::Run(const Task& task, TaskMeta& meta, Player& current,
                    Player& opponent, bool notify)
{
    const Task::lambda_t& role = task.GetTaskRole();
    meta = role(current, opponent);

    if (notify)
    {
        Notify(TaskMeta::CopyFrom(meta));
    }
}

void TaskAgent::Run(const std::vector<Task>& tasks, TaskMeta& meta,
                    Player& current, Player& opponent)
{
    TaskMeta temporal;
    std::vector<TaskMeta> pool;

    const auto copier = [](auto&& first, auto&& end, auto&& helper) {
        std::vector<TaskMeta> temporalPool;
        for (auto iter = first; iter != end; ++iter)
        {
            temporalPool.emplace_back(helper(*iter));
        }

        return temporalPool;
    };

    pool.reserve(tasks.size());
    auto begin = pool.begin();

    for (const auto& task : tasks)
    {
        Run(task, temporal, current, opponent, false);
        pool.emplace_back(std::move(temporal));

        // if TaskID::Brief, notify the meta data for after tasks
        if (task.GetTaskID() == +TaskID::BRIEF)
        {
            auto copied = copier(begin, pool.end(), TaskMeta::CopyFrom);
            Notify(Serializer::CreateTaskMetaVector(copied));

            begin = pool.end();
        }
    }

    meta = Serializer::CreateTaskMetaVector(pool);
    if (begin != pool.end())
    {
        if (begin == pool.begin())
        {
            // Notify Full task metas
            Notify(TaskMeta::CopyFrom(meta));
        }
        else
        {
            // Notify rest of task metas
            auto copied = copier(begin, pool.end(), std::move<TaskMeta&>);
            Notify(Serializer::CreateTaskMetaVector(copied));
        }
    }
}

void TaskAgent::Clear()
{
    m_tasks.clear();
}
}  // namespace Hearthstonepp