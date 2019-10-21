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
class IntAttr<T> : public Attr<T>
{
 public:
    virtual ~IntAttr() = default;

    void Apply(T* entity, EffectOperator effectOp, int value) override
    {
        std::optional<int>& target = GetRef(entity);

        if (effectOp == EffectOperator::SET)
        {
            target = value;
            return;
        }

        const int baseValue = target.value_or(GetCardValue(entity));

        switch (effectOp)
        {
            case EffectOperator::ADD:
                target = baseValue + value;
                break;
            case EffectOperator::SUB:
                target = baseValue - value;
                break;
            case EffectOperator::MUL:
                target = baseValue * value;
                break;
            default:
                throw std::invalid_argument(
                    "IntAttr::Apply() - Invalid effect operator!");
        }
    }

    void Remove(T* entity, EffectOperator effectOp, int value) override
    {
        std::optional<int>& target = GetRef(entity);

        if (!target.has_value())
        {
            return;
        }

        switch (effectOp)
        {
            case EffectOperator::ADD:
                target.value() -= value;
                break;
            case EffectOperator::SUB:
                target.value() += value;
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

        int& target = Attr<T>::GetAuraRef(auraEffects);

        switch (effectOp)
        {
            case EffectOperator::ADD:
                target += value;
                break;
            case EffectOperator::SUB:
                target -= value;
                break;
            case EffectOperator::MUL:
                target *= value;
                break;
            case EffectOperator::SET:
                GetRef(entity) = 0;
                target = value;
                break;
        }
    }

    void RemoveAura(T* entity, EffectOperator effectOp, int value) override
    {
        int& target = Attr<T>::GetAuraRef(entity->auraEffects);

        switch (effectOp)
        {
            case EffectOperator::ADD:
                target -= value;
                break;
            case EffectOperator::SUB:
                target += value;
                break;
            case EffectOperator::SET:
                target -= value;
                break;
            default:
                throw std::invalid_argument(
                    "IntAttr::RemoveAura() - Invalid effect operator!");
        }
    }

 protected:
    virtual std::optional<int>& GetRef(T* entity) = 0;

    virtual int GetCardValue(T* entity) = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ATTR_HPP
