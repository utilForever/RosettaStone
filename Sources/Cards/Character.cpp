/*************************************************************************
> File Name: Character.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Character class inherits from Card class.
> Created Time: 2018/06/17
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Character.h>
#include <Commons/Macros.h>

namespace Hearthstonepp
{
Character::Character(const Card* pCard) : Entity(pCard)
{
#ifndef HEARTHSTONEPP_MACOSX
    attack = pCard->attack.has_value() ? pCard->attack.value() : 0;
    health = pCard->health.has_value() ? pCard->health.value() : 0;
#else
    attack =
        (pCard->attack != std::experimental::nullopt) ? *(pCard->attack) : 0;
    health =
        (pCard->health != std::experimental::nullopt) ? *(pCard->health) : 0;
#endif
    maxHealth = health;
}

void Character::GetDataFromCard()
{
    
}
}