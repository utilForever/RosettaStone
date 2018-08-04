/*************************************************************************
> File Name: Enchantment.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Class to store attributes of the power of an enchantment card.
> Created Time: 2017/10/11
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Enchants/Enchant.h>

namespace Hearthstonepp
{
Enchant::Enchant(Effect& effect)
{
    m_effects.emplace_back(effect);
}
    
Enchant::Enchant(std::vector<Effect>& effects)
{
    m_effects = effects;
}

void Enchant::ActivateTo(Character* character)
{
    (void)character;
}
}