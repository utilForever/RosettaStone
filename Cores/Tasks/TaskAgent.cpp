/*************************************************************************
> File Name: TaskAgent.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Agent for managing Task Unit
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/TaskAgent.h>
#include <Tasks/TaskSerializer.h>

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
                    const ITask& task, bool notify)
{
    task.Run(player1, player2, meta);
    if (notify)
    {
        Notify(TaskMeta::CopyFrom(meta));
    }
}
}  // namespace Hearthstonepp