/*************************************************************************
> File Name: PowerTask.cpp
> Project Name: Hearthstonepp
> Author: Chan-Ho Chris Ohk
> Purpose: PowerTask that processes the power of card.
> Created Time: 2018/06/26
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Tasks/PowerTask.h>
#include <Tasks/PowerTasks/DestroyWeapon.h>

namespace Hearthstonepp::PowerTask
{
TaskID IPower::GetTaskID() const
{
    return TaskID::POWER_TASK;
}

void ProcessPower(Player& player1, Player& player2, PowerTaskType powerType)
{
    if (powerType == +PowerTaskType::DESTROY_OPPONENT_WEAPON)
    {
        DestroyWeapon().Run(player1, player2);
    }
}
}  // namespace Hearthstonepp::PowerTask