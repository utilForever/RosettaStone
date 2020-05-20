// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_EFFECT_HPP
#define ROSETTASTONE_PLAYMODE_EFFECT_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Enchants/IEffect.hpp>
#include <Rosetta/PlayMode/Enchants/PlayerAuraEffects.hpp>

namespace RosettaStone::PlayMode
{
class Entity;
class Playable;
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
class Effect : public IEffect
{
 public:
    //! Default constructor.
    Effect() = default;

    //! Constructs effect with given \p gameTag, \p effectOperator and \p value.
    //! \param gameTag The game tag of the card.
    //! \param effectOperator The effect operator to change card value.
    //! \param value The value to change.
    Effect(GameTag gameTag, EffectOperator effectOperator, int value);

    //! Default copy constructor.
    Effect(const Effect& effect) = default;

    //! Default move constructor;
    Effect(Effect&& effect) = default;

    //! Default copy assignment operator.
    Effect& operator=(const Effect& effect) = default;

    //! Default move assignment operator.
    Effect& operator=(Effect&& effect) = default;

    //! Applies effect to the target entity.
    //! \param entity An entity to which effect is applied.
    //! \param isOneTurnEffect Whether effect lasts only one turn.
    void ApplyTo(Entity* entity, bool isOneTurnEffect = false) const override;

    //! Applies effect to the target player as an aura effect.
    //! \param auraEffects The player aura effects.
    void ApplyTo(PlayerAuraEffects& auraEffects) const;

    //! Applies aura effect to the target entity.
    //! \param entity An entity to which aura effect is applied.
    void ApplyAuraTo(Entity* entity) const override;

    //! Removes effect from the target entity.
    //! \param entity An entity to which effect is removed.
    void RemoveFrom(Entity* entity) const override;

    //! Removes effect from the target player as an aura effect.
    //! \param auraEffects The player aura effects.
    void RemoveFrom(PlayerAuraEffects& auraEffects) const;

    //! Removes aura effect from the target entity.
    //! \param entity An entity to which aura effect is removed.
    void RemoveAuraFrom(Entity* entity) const override;

    //! Creates a new Effect having changed amount of \p newValue.
    //! \param newValue A value to change.
    //! \return A new Effect having changed amount.
    IEffect* ChangeValue(int newValue) const override;

    //! Returns the value of game tag.
    //! \return The value of game tag.
    GameTag GetGameTag() const;

    //! Returns the effect operator.
    //! \return The effect operator.
    EffectOperator GetEffectOperator() const;

    //! Returns the value of effect.
    //! \return The value of effect.
    int GetValue() const;

 private:
    GameTag m_gameTag = GameTag::INVALID;
    EffectOperator m_effectOperator = EffectOperator::SET;
    int m_value = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_EFFECT_HPP
