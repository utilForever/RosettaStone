/*************************************************************************
> File Name: Effect.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Represents an effect of auras or enchantment cards.
> Created Time: 2018/07/08
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Cards/Character.h>
#include <Enchants/Effect.h>

namespace Hearthstonepp
{
Effect::Effect(GameTag gameTag, EffectOperator effectOperator, int value)
    : m_gameTag(gameTag), m_effectOperator(effectOperator), m_value(value)
{
    // Do nothing
}

void Effect::Apply(Character* character, bool isOneTurnEffect) const
{
    if (isOneTurnEffect)
    {
        // TODO: Process one turn effect
    }

    switch (m_effectOperator)
    {
        case EffectOperator::ADD:
            character->gameTags[m_gameTag] += m_value;
            break;
        case EffectOperator::SUB:
            character->gameTags[m_gameTag] -= m_value;
            break;
        case EffectOperator::MUL:
            character->gameTags[m_gameTag] *= m_value;
            break;
        case EffectOperator::SET:
            character->gameTags[m_gameTag] = m_value;
            break;
        default:
            throw std::invalid_argument("Invalid effect operator!");
    }
}
}