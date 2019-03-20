// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Tasks/TaskWrapper.hpp>

namespace RosettaStone
{
DoBothPlayer::DoBothPlayer(ITask&& task) : m_task(task)
{
    // Do nothing
}

TaskID DoBothPlayer::GetTaskID() const
{
    return m_task.GetTaskID();
}

TaskStatus DoBothPlayer::Impl(Player& player)
{
    const TaskStatus status1 = m_task.Run(player);
    const TaskStatus status2 = m_task.Run(player.GetOpponent());

    if (status1 == status2)
    {
        return status1;
    }

    return status2;
}

DoUntil::DoUntil(ITask&& task, std::function<bool(TaskStatus)>&& condition)
    : m_task(task), m_condition(std::move(condition))
{
    // Do nothing
}

DoUntil::DoUntil(ITask&& task, TaskStatus id)
    : m_task(task), m_condition([=](TaskStatus meta) { return meta == id; })
{
    // Do nothing
}

TaskID DoUntil::GetTaskID() const
{
    return m_task.GetTaskID();
}

TaskStatus DoUntil::Impl(Player& player)
{
    TaskStatus status;

    while (true)
    {
        status = m_task.Run(player);

        // Do until the condition satisfied
        if (m_condition(status))
        {
            break;
        }
    }

    return status;
}
}  // namespace RosettaStone
