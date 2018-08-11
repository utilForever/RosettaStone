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

#include <vector>

namespace Hearthstonepp
{
class ITask;
struct Enchant;

struct Power
{
    std::vector<ITask*> powerTask;
    Enchant* enchant = nullptr;
};
}

#endif