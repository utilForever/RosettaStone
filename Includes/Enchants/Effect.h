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
struct Character;

//! Effect operator to change card value such as attack and health.
enum class EffectOperator
{
    ADD,  //!< Add card value.
    SUB,  //!< Subtract card value.
    MUL,  //!< Multiply card value.
    SET   //!< Set card value.
};

//!
//! \brief Effect class.
//!
//! This class represents an effect of auras or enchantment cards.
//!
class Effect
{
 public:
    //! Default constructor.
    Effect() = default;

    Effect(GameTag gameTag, EffectOperator effectOperator, int value);

    void Apply(Character* character, bool isOneTurnEffect = false) const;

 private:
    GameTag m_gameTag = GameTag::INVALID;
    EffectOperator m_effectOperator = EffectOperator::SET;
    int m_value = 0;
};
}

#endif