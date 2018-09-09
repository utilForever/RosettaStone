/*************************************************************************
> File Name: Weapon.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Weapon class inherits from Card class.
> Created Time: 2017/10/11
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Weapon.h>
#include <Commons/Macros.h>

namespace Hearthstonepp
{
Weapon::Weapon(const Card* pCard) : Entity(pCard)
{
#ifndef HEARTHSTONEPP_MACOSX
    durability = pCard->durability.has_value() ? pCard->durability.value() : 0;
#else
    durability = (pCard->durability != std::experimental::nullopt)
                     ? *(pCard->durability)
                     : 0;
#endif
}

Weapon::~Weapon()
{
    // Do nothing
}
}