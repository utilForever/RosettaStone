/*************************************************************************
> File Name: Effects.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Effects set characters' stats to a specified or
           context-specific value through an enchantment.
> Created Time: 2018/07/04
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_EFFECTS_H
#define HEARTHSTONEPP_EFFECTS_H

#include <Enchants/Effect.h>

namespace Hearthstonepp
{
struct Effects
{
    inline static Effect Taunt = Effect(GameTag::TAUNT, EffectOperator::SET, 1);
    inline static Effect Poisonous = Effect(GameTag::POISONOUS, EffectOperator::SET, 1);
    inline static Effect DvineShield = Effect(GameTag::DIVINE_SHIELD, EffectOperator::SET, 1);
    inline static Effect WindFury = Effect(GameTag::WINDFURY, EffectOperator::SET, 1);
    inline static Effect Stealth = Effect(GameTag::STEALTH, EffectOperator::SET, 1);
};
};

#endif