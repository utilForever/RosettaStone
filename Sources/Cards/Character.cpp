/*************************************************************************
> File Name: Character.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Character class inherits from Card class.
> Created Time: 2018/06/17
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Character.h>

namespace Hearthstonepp
{
Character::Character(const Card* pCard) : Entity(pCard)
{
    attack = pCard->attack.has_value() ? pCard->attack.value() : 0;
    health = pCard->health.has_value() ? pCard->health.value() : 0;
}

void Character::GetDataFromCard()
{
    
}
}