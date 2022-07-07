// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_INT_ATTR_HPP
#define ROSETTASTONE_PLAYMODE_INT_ATTR_HPP

#include <Rosetta/PlayMode/Enchants/Attrs/Attr.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
//!
//! \brief IntAttr class.
//!
//! This class inherits from Attr class and is template specialization
//! for the attribute that is integer type.
//!
template <typename T = Entity>
class IntAttr : public Attr<T>
{
 public:
    //! Default virtual destructor.
    virtual ~IntAttr() = default;

    //! Applies the effect that affects the attribute.
    //! \param entity The entity to apply the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void Apply(T* entity, EffectOperator effectOp, int value) override
    {
        const int target = GetValue(entity);

        switch (effectOp)
        {
            case EffectOperator::ADD:
                SetValue(entity, target + value);
                break;
            case EffectOperator::SUB:
                SetValue(entity, target - value);
                break;
            case EffectOperator::MUL:
                SetValue(entity, target * value);
                break;
            case EffectOperator::SET:
                SetValue(entity, value);
                break;
        }
    }

    //! Removes the effect that affects the attribute.
    //! \param entity The entity to remove the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void Remove(T* entity, EffectOperator effectOp, int value) override
    {
        const int target = GetValue(entity);

        switch (effectOp)
        {
            case EffectOperator::ADD:
                SetValue(entity, target - value);
                break;
            case EffectOperator::SUB:
                SetValue(entity, target + value);
                break;
            default:
                throw std::invalid_argument(
                    "IntAttr::Remove() - Invalid effect operator!");
        }
    }

    //! Applies the aura that affects the attribute.
    //! \param entity The entity to apply the aura.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void ApplyAura(T* entity, EffectOperator effectOp, int value) override
    {
        AuraEffects* auraEffects = entity->auraEffects;
        if (!auraEffects)
        {
            auraEffects = new AuraEffects(entity->card->GetCardType());
            entity->auraEffects = auraEffects;
        }

        const int target = GetAuraValue(auraEffects);

        switch (effectOp)
        {
            case EffectOperator::ADD:
                SetAuraValue(auraEffects, target + value);
                break;
            case EffectOperator::SUB:
                SetAuraValue(auraEffects, target - value);
                break;
            case EffectOperator::MUL:
                SetAuraValue(auraEffects, target * value);
                break;
            case EffectOperator::SET:
                SetValue(entity, 0);
                SetAuraValue(auraEffects, value);
                break;
        }
    }

    //! Removes the aura that affects the attribute.
    //! \param entity The entity to remove the aura.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void RemoveAura(T* entity, EffectOperator effectOp, int value) override
    {
        const int target = GetAuraValue(entity->auraEffects);

        switch (effectOp)
        {
            case EffectOperator::ADD:
                SetAuraValue(entity->auraEffects, target - value);
                break;
            case EffectOperator::SUB:
                SetAuraValue(entity->auraEffects, target + value);
                break;
            case EffectOperator::SET:
                SetAuraValue(entity->auraEffects, target - value);
                break;
            default:
                throw std::invalid_argument(
                    "IntAttr::RemoveAura() - Invalid effect operator!");
        }
    }

 protected:
    //! Returns the value of the attribute of the entity.
    //! \param entity The entity to get the value of the attribute.
    //! \return The value of the attribute of the entity.
    virtual int GetValue(T* entity) = 0;

    //! Sets the value of the attribute of the entity.
    //! \param entity The entity to set the value of the attribute.
    //! \param value The value of the attribute of the entity.
    virtual void SetValue(T* entity, int value) = 0;

    //! Returns the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \return The value the attribute that is affected by the aura effect.
    int GetAuraValue([[maybe_unused]] AuraEffects* auraEffects) override
    {
        throw std::logic_error("IntAttr::GetAuraValue() - Not implemented!");
    }

    //! Sets the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \param value The value the attribute that is affected by the aura
    //! effect.
    void SetAuraValue([[maybe_unused]] AuraEffects* auraEffects,
                      [[maybe_unused]] int value) override
    {
        throw std::logic_error("IntAttr::SetAuraValue() - Not implemented!");
    }
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_INT_ATTR_HPP
