/*************************************************************************
> File Name: Enchantment.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Enchantment class inherits from Card class.
> Created Time: 2017/09/16
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_ENCHANTMENT_H
#define HEARTHSTONEPP_ENCHANTMENT_H

#include <Models/Card.h>

namespace Hearthstonepp
{
struct Enchantment : public Card
{
    void ShowInfo() const override;
};
}

#endif