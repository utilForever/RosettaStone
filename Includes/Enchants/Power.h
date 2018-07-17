/*************************************************************************
> File Name: Power.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Power class that stores aura, enchant and so on.
> Created Time: 2018/06/23
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_POWER_H
#define HEARTHSTONEPP_POWER_H

#include <Enchants/Enchant.h>
#include <Enums/TaskEnums.h>

namespace Hearthstonepp
{
struct Enchant;

struct Power
{
    std::vector<PowerTaskType> powerTask;
    Enchant* enchant = nullptr;
};
}

#endif