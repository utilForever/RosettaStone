/*************************************************************************
> File Name: Tasks.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Task Unit for GameAgent
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_TASKS_H
#define HEARTHSTONEPP_TASKS_H

#include <Enums/CardEnums.h>
#include <Syncs/Player.h>
#include <Tasks/TaskMeta.h>

#include <functional>

namespace Hearthstonepp
{
class Task
{
 public:
    template <typename T>
    static constexpr inline bool is_task =
        std::is_same_v<std::decay_t<T>, Task>;

    // function object of runnable Task role.
    using lambda_t = std::function<TaskMeta(Player&, Player&)>;

    Task();

    Task(TaskID id, lambda_t&& role);
    Task(TaskID id, const lambda_t& role);

    Task(Task&& task);
    Task(const Task& task);

    Task& operator=(Task&& task);
    Task& operator=(const Task& task);

    TaskID GetTaskID() const;
    lambda_t GetTaskRole() const;

 private:
    TaskID m_id;
    lambda_t m_role;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKS_H
