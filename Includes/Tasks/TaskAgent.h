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

#include <Accounts/Player.h>
#include <Managers/SyncBuffer.h>
#include <Tasks/TaskMeta.h>
#include <Tasks/TaskSerializer.h>
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

    // Read TaskMeta from SyncBuffer
    // main channel as default, side channel by flag
    void Read(TaskMeta& meta, bool sideChannel = false);
    // Write TaskMeta from SyncBuffer,
    // main channel as default, side channel by flag
    void Notify(TaskMeta& meta, bool sideChannel = false);
    void Notify(TaskMeta&& meta, bool sideChannel = false);

    // Run single task and write result to `meta`,
    // if `notify` is true, TaskAgent notify the main channel as SyncBuffer
    void Run(TaskMeta& meta, Player& player1, Player& player2, ITask& task,
             bool notify = true);
    void Run(TaskMeta& meta, Player& player1, Player& player2, ITask&& task,
             bool notify = true);
    // Run Multi tasks and write result to `meta`
    template <typename... ITaskT>
    void RunMulti(TaskMeta& meta, Player& player1, Player& player2,
                  ITaskT&&... tasks)
    {
        std::vector<TaskMeta> pool;
        ImplRun(pool, player1, player2, std::forward<ITaskT>(tasks)...);

        meta = Serializer::CreateTaskMetaVector(pool);
        Notify(TaskMeta::CopyFrom(meta));
    }

 private:
    SyncBuffer<TaskMeta> m_syncBuffer;
    SyncBuffer<TaskMeta> m_sideChannel;

    template <typename... ITaskT>
    void ImplRun(std::vector<TaskMeta>& pool, Player& player1, Player& player2,
                 ITaskT&&... tasks)
    {
        auto pusher = [&, this](auto&& task) -> void {
            pool.emplace_back();
            TaskMeta& meta = pool.back();

            task.Run(player1, player2, meta);
            if (task.GetTaskID() == +TaskID::BRIEF)
            {
                Notify(std::move(meta));
                meta.status = MetaData::BRIEF_EXPIRED;
            }
        };
        (pusher(std::forward<ITaskT>(tasks)), ...);
    }
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKAGENT_H
