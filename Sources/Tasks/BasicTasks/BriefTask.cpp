/*************************************************************************
> File Name: Brief.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement Brief Task, Return GameStatus Immediately to GameInterface
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/BriefTask.h>

namespace Hearthstonepp::BasicTasks
{
TaskID BriefTask::GetTaskID() const
{
    return TaskID::BRIEF;
}

MetaData BriefTask::Impl(Player&, Player&)
{
    return MetaData::BRIEF;
}
}  // namespace Hearthstonepp::BasicTasks