/*************************************************************************
> File Name: Enchantment.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Class to store attributes of the power of an enchantment card.
> Created Time: 2017/09/16
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_ENCHANT_H
#define HEARTHSTONEPP_ENCHANT_H

#include <Enchants/Effect.h>

#include <vector>

namespace Hearthstonepp
{
struct Enchant
{
public:
    Enchant() = default;
    Enchant(Effect& effect);
    Enchant(std::vector<Effect>& effects);

    void ActivateTo(Entity& entity);

private:
    std::vector<Effect> m_effects;
};
}

#endif