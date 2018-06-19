/*************************************************************************
> File Name: Spell.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Spell class inherits from Card class.
> Created Time: 2017/09/16
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_SPELL_H
#define HEARTHSTONEPP_SPELL_H

#include <Cards/Card.h>

namespace Hearthstonepp
{
struct Spell : public Card
{
    void ShowInfo() const override;
};
}

#endif