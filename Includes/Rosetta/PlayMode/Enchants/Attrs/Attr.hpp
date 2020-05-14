// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ATTR_HPP
#define ROSETTASTONE_PLAYMODE_ATTR_HPP

#include <Rosetta/PlayMode/Models/Entity.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief Attr class.
//!
//! This class is an interface for attribute.
//!
template <typename T = Entity>
class Attr
{
 public:
    //! Default virtual destructor.
    virtual ~Attr() = default;

    //! Applies the effect that affects the attribute.
    //! \param entity The entity to apply the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    virtual void Apply(T* entity, EffectOperator effectOp, int value) = 0;

    //! Removes the effect that affects the attribute.
    //! \param entity The entity to remove the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    virtual void Remove(T* entity, EffectOperator effectOp, int value) = 0;

    //! Applies the aura that affects the attribute.
    //! \param entity The entity to apply the aura.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    virtual void ApplyAura(T* entity, EffectOperator effectOp, int value) = 0;

    //! Removes the aura that affects the attribute.
    //! \param entity The entity to remove the aura.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    virtual void RemoveAura(T* entity, EffectOperator effectOp, int value) = 0;

 protected:
    //! Returns the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \return The value the attribute that is affected by the aura effect.
    virtual int GetAuraValue(AuraEffects* auraEffects) = 0;

    //! Sets the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \param value The value the attribute that is affected by the aura
    //! effect.
    virtual void SetAuraValue(AuraEffects* auraEffects, int value) = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ATTR_HPP
