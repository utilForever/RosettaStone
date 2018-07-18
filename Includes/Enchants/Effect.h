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

#include <Cards/Entity.h>
#include <Enums/CardEnums.h>

namespace Hearthstonepp
{
struct Entity;

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
    Effect() = default;
    Effect(GameTag gameTag, EffectOperator effectOperator, int value);

    void Apply(Entity& entity, bool isOneTurnEffect = false) const;

private:
    GameTag m_gameTag = GameTag::INVALID;
    EffectOperator m_effectOperator = EffectOperator::SET;
    int m_value = 0;
};
}

#endif