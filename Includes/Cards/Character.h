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

#include <Cards/Entity.h>

namespace Hearthstonepp
{
struct Character : public Entity
{
    Character() = default;
    Character(const Card* pCard);
    virtual ~Character() = default;

    void GetDataFromCard() override;

    size_t attack = 0;
    size_t health = 0;
};
}

#endif