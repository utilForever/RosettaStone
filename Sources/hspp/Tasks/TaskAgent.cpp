// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/TaskAgent.hpp>
#include <hspp/Tasks/TaskSerializer.hpp>

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

void TaskAgent::Run(TaskMeta& meta, Player& player, ITask& task, bool notify)
{
    task.Run(player, meta);
    if (notify)
    {
        Notify(TaskMeta::CopyFrom(meta));
    }
}

void TaskAgent::Run(TaskMeta& meta, Player& player, ITask&& task, bool notify)
{
    task.Run(player, meta);
    if (notify)
    {
        Notify(TaskMeta::CopyFrom(meta));
    }
}
}  // namespace Hearthstonepp
