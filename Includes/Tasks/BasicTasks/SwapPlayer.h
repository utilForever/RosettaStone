/*************************************************************************
> File Name: SwapPlayer.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_SWAPPLAYER_H
#define HEARTHSTONEPP_SWAPPLAYER_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class SwapPlayerTask : public ITask
{
 public:
    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_SWAPPLAYER_H
