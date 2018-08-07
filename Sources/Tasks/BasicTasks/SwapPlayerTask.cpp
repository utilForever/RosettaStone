/*************************************************************************
> File Name: SwapPlayer.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement SwapPlayerTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/SwapPlayerTask.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
TaskID SwapPlayerTask::GetTaskID() const
{
    return TaskID::SWAP;
}

MetaData SwapPlayerTask::Impl(Player& player1, Player& player2)
{
    std::swap(player1, player2);
    return MetaData::SWAP_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks