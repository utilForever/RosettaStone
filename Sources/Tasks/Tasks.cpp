/*************************************************************************
> File Name: Tasks.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Task Unit for GameAgent
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/TaskSerializer.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp
{
MetaData ITask::Run(Player& player1, Player& player2)
{
    return Impl(player1, player2);
}

MetaData ITask::Run(Player& player1, Player& player2, TaskMeta& meta)
{
    MetaData status = Impl(player1, player2);
    meta = Serializer::CreateGameStatus(GetTaskID(), status, player1, player2);

    return status;
}

TaskID ITask::GetTaskID() const
{
    return TaskID::INVALID;
}
}  // namespace Hearthstonepp
