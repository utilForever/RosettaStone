#ifndef HEARTHSTONEPP_TASKAGENT_H
#define HEARTHSTONEPP_TASKAGENT_H

#include <hspp/Accounts/Player.h>
#include <hspp/Managers/SyncBuffer.h>
#include <hspp/Tasks/TaskMeta.h>
#include <hspp/Tasks/TaskSerializer.h>
#include <hspp/Tasks/Tasks.h>

#include <vector>

namespace Hearthstonepp
{
//!
//! \brief TaskAgent class.
//!
//! This class runs single/multiple task(s).
//! Also, it reads/writes task meta from/to synchronized buffer.
//!
class TaskAgent
{
 public:
    //! Default constructor.
    TaskAgent() = default;

    //! Deleted copy constructor.
    TaskAgent(const TaskAgent&) = delete;

    //! Deleted move constructor.
    TaskAgent(TaskAgent&&) = delete;

    //! Deleted copy assignment operator.
    TaskAgent& operator=(TaskAgent&&) = delete;

    //! Deleted move assignment operator.
    TaskAgent& operator=(const TaskAgent&) = delete;

    //! Reads task meta from synchronized buffer.
    //! \param meta A task meta data to write to task agent.
    //! \param sideChannel A variable that tells you whether to use side.
    void Read(TaskMeta& meta, bool sideChannel = false);

    //! Writes task meta to synchronized buffer.
    //! \param meta A task meta data to write to task agent (lvalue ref).
    //! \param sideChannel A variable that tells you whether to use side.
    void Notify(TaskMeta& meta, bool sideChannel = false);

    //! Writes task meta to synchronized buffer.
    //! \param meta A task meta data to write to task agent (rvalue ref).
    //! \param sideChannel A variable that tells you whether to use side.
    void Notify(TaskMeta&& meta, bool sideChannel = false);

    //! Runs single task and write the result to \p meta.
    //! \param meta A task meta that defines return status of task.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \param task The task to run (lvalue ref).
    //! \param notify Writes \p meta to synchronized buffer if it is true.
    void Run(TaskMeta& meta, Player& player1, Player& player2, ITask& task,
             bool notify = true);

    //! Runs single task and write the result to \p meta.
    //! \param meta A task meta that defines return status of task.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \param task The task to run (rvalue ref).
    //! \param notify Writes \p meta to synchronized buffer if it is true.
    void Run(TaskMeta& meta, Player& player1, Player& player2, ITask&& task,
             bool notify = true);

    //! Runs multiple tasks and write the result to \p meta.
    //! \tparam ITaskT The type of task.
    //! \param meta A task meta that defines return status of task.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \param tasks The task to run (variadic template).
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
    //! Internal implementation methods of Run().
    //! \tparam ITaskT The type of task.
    //! \param pool A task meta pool that stores task list.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \param tasks The task to run (variadic template).
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

    SyncBuffer<TaskMeta> m_syncBuffer;
    SyncBuffer<TaskMeta> m_sideChannel;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKAGENT_H
