/*************************************************************************
> File Name: PowerTask.h
> Project Name: Hearthstonepp
> Author: Chan-Ho Chris Ohk
> Purpose: PowerTask that processes the power of card.
> Created Time: 2018/06/26
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_POWER_TASK_H
#define HEARTHSTONEPP_POWER_TASK_H

#include <Managers/Player.h>
#include <Tasks/TaskMeta.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
void ProcessPower(Player& player1, Player& player2, PowerTaskType powerType);

// Interface of Power Tasks
class IPower : public ITask
{
 public:
    TaskID GetTaskID() const override;
    virtual PowerTaskType GetPowerType() const = 0;

 private:
    virtual MetaData Impl(Player& player1, Player& player2) const = 0;
};
}  // namespace Hearthstonepp::PowerTask

#endif