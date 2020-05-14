// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_IEFFECT_HPP
#define ROSETTASTONE_PLAYMODE_IEFFECT_HPP

namespace RosettaStone::PlayMode
{
class Entity;

//!
//! \brief IEffect class.
//!
//! This class is an interface for effect.
//!
class IEffect
{
 public:
    //! Default destructor.
    virtual ~IEffect() = default;

    //! Applies effect to the target entity.
    //! \param entity An entity to which effect is applied.
    //! \param isOneTurnEffect Whether effect lasts only one turn.
    virtual void ApplyTo(Entity* entity,
                         bool isOneTurnEffect = false) const = 0;

    //! Applies aura effect to the target entity.
    //! \param entity An entity to which aura effect is applied.
    virtual void ApplyAuraTo(Entity* entity) const = 0;

    //! Removes effect from the target entity.
    //! \param entity An entity to which effect is removed.
    virtual void RemoveFrom(Entity* entity) const = 0;

    //! Removes aura effect from the target entity.
    //! \param entity An entity to which aura effect is removed.
    virtual void RemoveAuraFrom(Entity* entity) const = 0;

    //! Creates a new Effect having changed amount of \p newValue.
    //! \param newValue A value to change.
    //! \return A new Effect having changed amount.
    virtual IEffect* ChangeValue(int newValue) const = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_IEFFECT_HPP
