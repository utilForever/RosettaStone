/*************************************************************************
> File Name: Enchantment.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Enchantment class inherits from Card class.
> Created Time: 2018/07/11
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_ENCHANTMENT_H
#define HEARTHSTONEPP_ENCHANTMENT_H

#include <Cards/Entity.h>

namespace Hearthstonepp
{
struct Enchantment : public Entity
{
    void GetDataFromCard() override;
};
}

#endif