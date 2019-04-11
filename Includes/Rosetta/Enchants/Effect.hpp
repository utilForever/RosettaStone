// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_EFFECT_HPP
#define ROSETTASTONE_EFFECT_HPP

#include <Rosetta/Enums/CardEnums.hpp>

namespace RosettaStone
{
class Character;
class AuraEffects;

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

    //! Constructs effect with given \p gameTag, \p effectOperator and \p value.
    //! \param gameTag The game tag of the card.
    //! \param effectOperator The effect operator to change card value.
    //! \param value The value to change.
    Effect(GameTag gameTag, EffectOperator effectOperator, int value);

    //! Applies this effect to the target entity.
    //! \param character The character to which effect is applied.
    //! \param isOneTurnEffect Whether effect lasts only one turn.
    void Apply(Character* character, bool isOneTurnEffect = false) const;

    //! Applies this effect to the target as an aura effect.
    //! \param auraEffects The aura effect.
    void Apply(AuraEffects& auraEffects) const;

    //! Removes this aura effect from the target entity.
    //! \param character The character to which effect is removed.
    void Remove(Character* character) const;

    //! Removes this aura effect from the target entity.
    //! \param auraEffects The aura effect.
    void Remove(AuraEffects& auraEffects) const;

 private:
    GameTag m_gameTag = GameTag::INVALID;
    EffectOperator m_effectOperator = EffectOperator::SET;
    int m_value = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EFFECT_HPP
