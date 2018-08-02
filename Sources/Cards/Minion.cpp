/*************************************************************************
> File Name: Minion.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Minion class inherits from Card class.
> Created Time: 2017/10/11
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Minion.h>

namespace Hearthstonepp
{
Minion::Minion(const Card* pCard) : Character(pCard)
{
    // Do nothing
}

Minion::~Minion()
{
}
}