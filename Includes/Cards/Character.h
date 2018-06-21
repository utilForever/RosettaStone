/*************************************************************************
> File Name: Character.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Character class inherits from Card class.
> Created Time: 2018/06/17
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CHARACTER_H
#define HEARTHSTONEPP_CHARACTER_H

#include <Cards/Card.h>

namespace Hearthstonepp
{
struct Character : public Card
{
    void ShowInfo() const override;

    size_t attack;
    size_t health;
};
}

#endif