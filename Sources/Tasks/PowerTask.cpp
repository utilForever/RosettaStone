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
TaskMeta DestroyWeapon(Player& player)
{
    delete player.hero->weapon;

    std::vector<TaskMeta> vector;
    return Serializer::CreateTaskMetaVector(vector);
}
}