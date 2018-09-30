// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/TaskSerializer.h>

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

void TaskAgent::Notify(TaskMeta& meta, bool sideChannel)
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

void TaskAgent::Run(TaskMeta& meta, Player& player1, Player& player2,
                    ITask& task, bool notify)
{
    task.Run(player1, player2, meta);
    if (notify)
    {
        Notify(TaskMeta::CopyFrom(meta));
    }
}

void TaskAgent::Run(TaskMeta& meta, Player& player1, Player& player2,
                    ITask&& task, bool notify)
{
    task.Run(player1, player2, meta);
    if (notify)
    {
        Notify(TaskMeta::CopyFrom(meta));
    }
}
}  // namespace Hearthstonepp
