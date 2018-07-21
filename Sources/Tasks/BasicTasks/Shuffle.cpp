/*************************************************************************
> File Name: Shuffle.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/Shuffle.h>

#include <random>

namespace Hearthstonepp::BasicTasks
{
TaskID ShuffleTask::GetTaskID() const
{
    return TaskID::SHUFFLE;
}

MetaData ShuffleTask::Impl(Player& player1, Player&) const
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(player1.cards.begin(), player1.cards.end(), gen);

    return MetaData::SHUFFLE_SUCCESS;
}
}  // namespace Hearthstonepp