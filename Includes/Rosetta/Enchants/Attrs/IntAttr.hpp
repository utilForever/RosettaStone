// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_INT_ATTR_HPP
#define ROSETTASTONE_INT_ATTR_HPP

#include <Rosetta/Enchants/Attrs/Attr.hpp>

namespace RosettaStone
{
template <typename T = Entity>
class IntAttr : public Attr<T>
{
 public:
    virtual ~IntAttr() = default;

    void Apply(T* entity, EffectOperator effectOp, int value) override
    {
        const int target = GetValue(entity);

        if (effectOp == EffectOperator::SET)
        {
            SetValue(entity, value);
            return;
        }

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
            default:
                throw std::invalid_argument(
                    "IntAttr::Apply() - Invalid effect operator!");
        }
    }

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

    void ApplyAura(T* entity, EffectOperator effectOp, int value) override
    {
        AuraEffects* auraEffects = entity->auraEffects;
        if (auraEffects == nullptr)
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
    virtual int GetValue(T* entity) = 0;

    virtual void SetValue(T* entity, int value) = 0;

    int GetAuraValue(AuraEffects* auraEffects) override
    {
        throw std::logic_error("Cost::GetAuraValue() - Not implemented!");
    }

    void SetAuraValue(AuraEffects* auraEffects, int value) override
    {
        throw std::logic_error("Cost::GetAuraValue() - Not implemented!");
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ATTR_HPP
