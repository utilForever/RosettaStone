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

#include <Syncs/AgentStructures.h>
#include <Syncs/SyncBuffer.h>
#include <Tasks/TaskMeta.h>
#include <Tasks/Tasks.h>

#include <vector>

namespace Hearthstonepp
{
class TaskAgent
{
 public:
    TaskAgent() = default;

    // Non copy-assignable class
    TaskAgent(TaskAgent&&) = delete;
    TaskAgent(const TaskAgent&) = delete;

    TaskAgent& operator=(TaskAgent&&) = delete;
    TaskAgent& operator=(const TaskAgent&) = delete;

    // Read TaskMeta from SyncBuffer, main channel as default, side channel by
    // true flag
    void Read(TaskMeta& meta, bool sideChannel = false);
    // Write TaskMeta from SyncBuffer, main channel as default, side channel by
    // true flag
    void Notify(TaskMeta&& meta, bool sideChannel = false);

    // Alias of Run(m_tasks, meta, current, opponent)
    void Run(TaskMeta& meta, Player& current, Player& opponent);
    // Run single task and write result to `meta`,
    // if `notify` is true, TaskAgent notify the SyncBuffer in main channel
    void Run(const Task& task, TaskMeta& meta, Player& current,
             Player& opponent, bool notify = true);
    // Run Multi task and write result to `meta`
    void Run(const std::vector<Task>& tasks, TaskMeta& meta, Player& current,
             Player& opponent);

    // Clear task meta vector
    void Clear();

    // Add task to task vector
    template <class T, typename = std::enable_if_t<Task::is_task<T>>>
    void Add(T&& task)
    {
        m_tasks.emplace_back(std::forward<T>(task));
    }

 private:
    SyncBuffer<TaskMeta> m_syncBuffer;
    SyncBuffer<TaskMeta> m_sideChannel;

    std::vector<Task> m_tasks;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKAGENT_H
