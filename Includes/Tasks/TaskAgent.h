/*************************************************************************
> File Name: TaskAgent.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Agent for managing Task Unit
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_TASKAGENT_H
#define HEARTHSTONEPP_TASKAGENT_H

#include <Tasks/TaskMeta.h>

#include <vector>

namespace Hearthstonepp
{
    class TaskAgent
    {
    public:
        TaskAgent() = default;

        TaskAgent(TaskAgent&&) = delete;
        TaskAgent(const TaskAgent&) = delete;

        TaskAgent& operator=(TaskAgent&&) = delete;
        TaskAgent& operator=(const TaskAgent&) = delete;

        void Read(TaskMeta& meta, bool sideChannel = false);
        void Notify(TaskMeta&& meta, bool sideChannel = false);

        void Run(TaskMeta& meta, User& current, User& opponent);
        void Run(const Task& task, TaskMeta& meta, User& current, User& opponent, bool notify = true);
        void Run(const std::vector<Task>& tasks, TaskMeta& meta, User& current, User& opponent);

        template <class T, typename = std::enable_if_t<is_task<T>>>
        void Add(T&& task)
        {
            m_tasks.emplace_back(std::forward<T>(task));
        }

    private:
        SyncBuffer<TaskMeta> m_syncBuffer;
        SyncBuffer<TaskMeta> m_sideChannel;

        std::vector<Task> m_tasks;

        template <typename T>
        static constexpr inline bool is_task = std::is_same_v<std::decay_t<T>, Task>;
    };
}

#endif //HEARTHSTONEPP_TASKAGENT_H
