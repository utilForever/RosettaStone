/*************************************************************************
> File Name: Tasks.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Task Unit for GameAgent
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/Tasks.h>

namespace Hearthstonepp
{
Task::Task() : m_id(TaskID::INVALID)
{
    // Do Nothing
}

Task::Task(TaskID id, lambda_t&& role) : m_id(id), m_role(std::move(role))
{
    // Do Nothing
}

Task::Task(TaskID id, const lambda_t& role) : m_id(id), m_role(role)
{
    // Do Nothing
}

Task::Task(Task&& task)
    : m_id(task.GetTaskID()), m_role(task.GetTaskRole())
{
    // Do Nothing
}

Task::Task(const Task& task)
    : m_id(task.GetTaskID()), m_role(task.GetTaskRole())
{
    // Do Nothing
}

Task& Task::operator=(Task&& task)
{
    m_id = task.GetTaskID();
    m_role = task.GetTaskRole();

    return *this;
}

Task& Task::operator=(const Task& task)
{
    m_id = task.GetTaskID();
    m_role = task.GetTaskRole();

    return *this;
}

TaskID Task::GetTaskID() const
{
    return m_id;
}

Task::lambda_t Task::GetTaskRole() const
{
    return m_role;
}
}  // namespace Hearthstonepp
