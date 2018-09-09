/*************************************************************************
> File Name: Weapon.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Weapon class inherits from Card class.
> Created Time: 2017/09/16
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_WEAPON_H
#define HEARTHSTONEPP_WEAPON_H

#include <Cards/Entity.h>

namespace Hearthstonepp
{
struct Weapon : public Entity
{
    Weapon() = default;
    Weapon(const Card* pCard);
    virtual ~Weapon();

    size_t durability = 0;
};
}

#endif