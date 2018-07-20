/*************************************************************************
> File Name: PowerTask.cpp
> Project Name: Hearthstonepp
> Author: Chan-Ho Chris Ohk
> Purpose: PowerTask that processes the power of card.
> Created Time: 2018/06/26
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Tasks/PowerTask.h>
#include <Tasks/TaskSerializer.h>

namespace Hearthstonepp::PowerTask
{
TaskMeta ProcessPower(Player& player, Player& opponent, PowerTaskType powerType)
{
    (void)player;

    if (powerType == +PowerTaskType::DESTROY_OPPONENT_WEAPON)
    {
        return DestroyWeapon(opponent);
    }

    std::vector<TaskMeta> vector;
    return Serializer::CreateTaskMetaVector(vector);
}

TaskMeta DestroyWeapon(Player& player)
{
    player.hero->weapon = nullptr;

    std::vector<TaskMeta> vector;
    return Serializer::CreateTaskMetaVector(vector);
}
}