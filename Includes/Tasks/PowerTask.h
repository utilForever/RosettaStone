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

#include <Syncs/AgentStructures.h>
#include <Tasks/TaskMeta.h>

namespace Hearthstonepp::PowerTask
{
TaskMeta ProcessPower(Player& player, Player& opponent,
                      PowerTaskType powerType);
TaskMeta DestroyWeapon(Player& player);
}

#endif