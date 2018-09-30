// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/TaskWrapper.h>

namespace Hearthstonepp::BasicTasks
{
DoBothPlayer::DoBothPlayer(ITask&& task) : m_task(task)
{
    // Do Nothign
}

TaskID DoBothPlayer::GetTaskID() const
{
    return m_task.GetTaskID();
}

MetaData DoBothPlayer::Impl(Player& player1, Player& player2)
{
    MetaData status1 = m_task.Run(player1, player2);
    MetaData status2 = m_task.Run(player2, player1);

    if (status1 == status2)
    {
        return status1;
    }
    else
    {
        return status2;
    }
}

DoUntil::DoUntil(ITask&& task, std::function<bool(const TaskMeta&)>&& condition)
    : m_task(task), m_condition(std::move(condition))
{
    // Do Nothing
}

TaskID DoUntil::GetTaskID() const
{
    return m_task.GetTaskID();
}

MetaData DoUntil::Impl(Player& player1, Player& player2)
{
    TaskMeta meta;
    while (true)
    {
        m_task.Run(player1, player2, meta);
        // Do until the condition satisfied
        if (m_condition(meta))
        {
            break;
        }
    }

    return meta.status;
}
}  // namespace Hearthstonepp::BasicTasks