/*************************************************************************
> File Name: Effect.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Represents an effect of auras or enchantment cards.
> Created Time: 2018/07/07
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_EFFECT_H
#define HEARTHSTONEPP_EFFECT_H

#include <Enums/CardEnums.h>

namespace Hearthstonepp
{
enum class EffectOperator
{
    ADD,
    SUB,
    MUL,
    SET
};

struct Effect
{
public:
    Effect(GameTag gameTag, EffectOperator effectOperator, int value);

private:
    GameTag m_gameTag;
    EffectOperator m_effectOperator;
    int m_value;
};
}

#endif