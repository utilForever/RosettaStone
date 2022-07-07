// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_BOOL_ATTR_HPP
#define ROSETTASTONE_PLAYMODE_BOOL_ATTR_HPP

#include <Rosetta/PlayMode/Enchants/Attrs/Attr.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
//!
//! \brief BoolAttr class.
//!
//! This class inherits from Attr class and is template specialization
//! for the attribute that is boolean type.
//!
template <typename T = Entity>
class BoolAttr : public Attr<T>
{
 public:
    //! Default virtual destructor.
    virtual ~BoolAttr() = default;

    //! Applies the effect that affects the attribute.
    //! \param entity The entity to apply the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void Apply(T* entity, EffectOperator effectOp, int value) override
    {
        if (effectOp != EffectOperator::SET)
        {
            throw std::invalid_argument(
                "BoolAttr::Apply() - Invalid effect operator!");
        }

        SetValue(entity, value > 0);
    }

    //! Removes the effect that affects the attribute.
    //! \param entity The entity to remove the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void Remove(T* entity, [[maybe_unused]] EffectOperator effectOp,
                [[maybe_unused]] int value) override
    {
        SetValue(entity, false);
    }

    //! Applies the aura that affects the attribute.
    //! \param entity The entity to apply the aura.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void ApplyAura(T* entity, [[maybe_unused]] EffectOperator effectOp,
                   [[maybe_unused]] int value) override
    {
        AuraEffects* auraEffects = entity->auraEffects;
        if (!auraEffects)
        {
            auraEffects = new AuraEffects(entity->card->GetCardType());
            entity->auraEffects = auraEffects;
        }

        const int target = Attr<T>::GetAuraValue(auraEffects);
        Attr<T>::SetAuraValue(auraEffects, target + 1);
    }

    //! Removes the aura that affects the attribute.
    //! \param entity The entity to remove the aura.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void RemoveAura(T* entity, [[maybe_unused]] EffectOperator effectOp,
                    [[maybe_unused]] int value) override
    {
        const int target = Attr<T>::GetAuraValue(entity->auraEffects);
        Attr<T>::SetAuraValue(entity->auraEffects, target - 1);
    }

 protected:
    //! Returns the value of the attribute of the entity.
    //! \param entity The entity to get the value of the attribute.
    //! \return The value of the attribute of the entity.
    virtual bool GetValue(T* entity) = 0;

    //! Sets the value of the attribute of the entity.
    //! \param entity The entity to set the value of the attribute.
    //! \param value The value of the attribute of the entity.
    virtual void SetValue(T* entity, bool value) = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_BOOL_ATTR_HPP
