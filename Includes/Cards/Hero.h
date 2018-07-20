/*************************************************************************
> File Name: Hero.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hero class inherits from Card class.
> Created Time: 2017/08/21
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_HERO_H
#define HEARTHSTONEPP_HERO_H

#include <Cards/Character.h>
#include <Cards/Weapon.h>

namespace Hearthstonepp
{
struct Hero : public Character
{
    Hero(const Card* pCard);

    Weapon* weapon;
};
}

#endif