/*************************************************************************
> File Name: InitAttackCountTask.h
> Project Name: Hearthstonepp
> Author: Seung-Hyun Jeon
> Purpose: Implement Init Attack Count
> Created Time: 2018/08/15
> Copyright (c) 2018, Seung-Hyun Jeon
*************************************************************************/
#ifndef HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H
#define HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H

#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{

class InitAttackCountTask : public ITask
{
  public:
    InitAttackCountTask();
    TaskID GetTaskID() const override;

  private:
    MetaData Impl(Player& player1, Player& player2) override;
};

}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_INIT_ATTACK_COUNT_TASK_H
