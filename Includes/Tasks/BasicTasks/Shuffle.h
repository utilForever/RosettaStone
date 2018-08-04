/*************************************************************************
> File Name: Shuffle.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement ShuffleTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_SHUFFLE_H
#define HEARTHSTONEPP_SHUFFLE_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class ShuffleTask : public ITask
{
 public:
    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_SHUFFLE_H
