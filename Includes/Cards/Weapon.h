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

#include <Models/Card.h>

namespace Hearthstonepp
{
struct Weapon : public Card
{
    void ShowInfo() const override;

    size_t attack;
    size_t durability;
};
}

#endif