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

    void TaskAgent::Run(TaskMeta& meta, User& current, User &opponent)
    {
        Run(m_tasks, meta, current, opponent);
    }

    void TaskAgent::Run(const Task& task, TaskMeta& meta, User& current, User& opponent, bool notify)
    {
        const Task::lambda_t& role = task.GetTaskRole();
        meta = std::move(role(current, opponent));

        if (notify)
        {
            Notify(TaskMeta::CopyFrom(meta));
        }
    }

    void TaskAgent::Run(const std::vector<Task>& tasks, TaskMeta &meta, User& current, User& opponent)
    {
        TaskMeta temporal;
        std::vector<TaskMeta> pool;

        for (const auto& task : tasks)
        {
            Run(task, temporal, current, opponent, false);
            pool.emplace_back(std::move(temporal));
        }

        Serializer::CreateTaskMetaVector(meta, pool);
        Notify(TaskMeta::CopyFrom(meta));
    }
}