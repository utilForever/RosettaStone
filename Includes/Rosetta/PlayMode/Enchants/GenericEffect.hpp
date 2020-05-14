// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_GENERIC_EFFECT_HPP
#define ROSETTASTONE_PLAYMODE_GENERIC_EFFECT_HPP

#include <Rosetta/PlayMode/Enchants/Attrs/Attr.hpp>
#include <Rosetta/PlayMode/Enchants/IEffect.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief GenericEffect class.
//!
//! This class is a simple container for saving game tag such as GameTag::ATK,
//! GameTag::COST and GameTag::HEALTH.
//!
template <typename T = Playable, typename AttrT = Attr<T>>
class GenericEffect : public IEffect
{
 public:
    //! Constructs generic effect with given \p attr, \p effectOp and \p value.
    //! \param attr The attribute to change.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    GenericEffect(std::shared_ptr<AttrT> attr, EffectOperator effectOp,
                  int value)
        : m_attr(std::move(attr)), m_effectOp(effectOp), m_value(value)
    {
        // Do nothing
    }

    //! Applies effect to the target entity.
    //! \param entity An entity to which effect is applied.
    //! \param isOneTurnEffect Whether effect lasts only one turn.
    void ApplyTo(Entity* entity, bool isOneTurnEffect = false) const override
    {
        if (isOneTurnEffect)
        {
            entity->game->oneTurnEffects.emplace_back(
                entity, const_cast<GenericEffect<T, AttrT>*>(this));
        }

        m_attr->Apply(entity, m_effectOp, m_value);
    }

    //! Applies aura effect to the target entity.
    //! \param entity An entity to which aura effect is applied.
    void ApplyAuraTo(Entity* entity) const override
    {
        m_attr->ApplyAura(entity, m_effectOp, m_value);
    }

    //! Removes effect from the target entity.
    //! \param entity An entity to which effect is removed.
    void RemoveFrom(Entity* entity) const override
    {
        m_attr->Remove(entity, m_effectOp, m_value);
    }

    //! Removes aura effect from the target entity.
    //! \param entity An entity to which aura effect is removed.
    void RemoveAuraFrom(Entity* entity) const override
    {
        m_attr->RemoveAura(entity, m_effectOp, m_value);
    }

    //! Creates a new Effect having changed amount of \p newValue.
    //! \param newValue A value to change.
    //! \return A new Effect having changed amount.
    IEffect* ChangeValue(int newValue) const override
    {
        return new GenericEffect<T, AttrT>(m_attr, m_effectOp, newValue);
    }

 private:
    std::shared_ptr<AttrT> m_attr;
    EffectOperator m_effectOp;
    int m_value;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_GENERIC_EFFECT_HPP
