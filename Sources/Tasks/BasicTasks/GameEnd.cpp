/*************************************************************************
> File Name: GameEnd.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement GameEndTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/GameEnd.h>

namespace Hearthstonepp::BasicTasks
{
TaskID GameEndTask::GetTaskID() const
{
    return TaskID::GAME_END;
}

MetaData GameEndTask::Impl(Player&, Player&)
{
    return MetaData::GAME_END;
}
}  // namespace Hearthstonepp::BasicTasks