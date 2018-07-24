/*************************************************************************
> File Name: GameEnd.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement GameEndTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_GAMEEND_H
#define HEARTHSTONEPP_GAMEEND_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class GameEndTask : public ITask
{
 public:
    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_GAMEEND_H
