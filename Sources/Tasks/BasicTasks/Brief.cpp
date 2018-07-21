/*************************************************************************
> File Name: Brief.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/Brief.h>

namespace Hearthstonepp::BasicTasks
{
TaskID BriefTask::GetTaskID() const
{
    return TaskID::BRIEF;
}

MetaData BriefTask::Impl(Player&, Player&) const
{
    return MetaData::BRIEF;
}
}  // namespace Hearthstonepp