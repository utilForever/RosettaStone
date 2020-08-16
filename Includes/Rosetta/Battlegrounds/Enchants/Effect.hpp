// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_EFFECT_HPP
#define ROSETTASTONE_BATTLEGROUNDS_EFFECT_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

namespace RosettaStone::Battlegrounds
{
class Minion;

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
    //! Constructs effect with given \p gameTag, \p effectOperator and \p value.
    //! \param gameTag The game tag of the card.
    //! \param effectOperator The effect operator to change card value.
    //! \param value The value to change.
    Effect(GameTag gameTag, EffectOperator effectOperator, int value);

    //! Gets the value according to game tag.
    //! \param minion A minion to get the value.
    //! \return The value according to game tag.
    int GetValue(Minion& minion) const;

    //! Sets the value according to game tag.
    //! \param minion A minion to set the value.
    //! \param value The value according to game tag.
    void SetValue(Minion& minion, int value) const;

    //! Applies effect to the target minion.
    //! \param minion A minion to which effect is applied.
    void ApplyTo(Minion& minion) const;

    //! Creates a new Effect having changed amount of \p newValue.
    //! \param newValue A value to change.
    //! \return A new Effect having changed amount.
    Effect ChangeValue(int newValue) const;

 private:
    GameTag m_gameTag = GameTag::INVALID;
    EffectOperator m_effectOperator = EffectOperator::SET;
    int m_value = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_EFFECT_HPP
