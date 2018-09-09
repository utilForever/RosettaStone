/*************************************************************************
> File Name: HeroPower.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: HeroPower class inherits from Card class.
> Created Time: 2017/09/16
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_HERO_POWER_H
#define HEARTHSTONEPP_HERO_POWER_H

#include <Cards/Entity.h>

namespace Hearthstonepp
{
struct HeroPower : public Entity
{
    HeroPower(const Card* pCard);
};
}

#endif