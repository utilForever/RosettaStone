/*************************************************************************
> File Name: Effect.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Represents an effect of auras or enchantment cards.
> Created Time: 2018/07/08
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Enchants/Effect.h>

namespace Hearthstonepp
{
Effect::Effect(GameTag gameTag, EffectOperator effectOperator, int value)
    : m_gameTag(gameTag), m_effectOperator(effectOperator), m_value(value)
{
    // Do nothing
}
}