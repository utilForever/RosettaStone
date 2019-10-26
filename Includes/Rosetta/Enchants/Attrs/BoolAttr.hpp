// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BOOL_ATTR_HPP
#define ROSETTASTONE_BOOL_ATTR_HPP

#include <Rosetta/Enchants/Attrs/Attr.hpp>

#include <stdexcept>

namespace RosettaStone
{
template <typename T = Entity>
class BoolAttr : public Attr<T>
{
 public:
    virtual ~BoolAttr() = default;

    void Apply(T* entity, EffectOperator effectOp, int value) override
    {
        if (effectOp != EffectOperator::SET)
        {
            throw std::invalid_argument(
                "BoolAttr::Apply() - Invalid effect operator!");
        }

        SetValue(entity, value > 0);
    }

    void Remove(T* entity, [[maybe_unused]] EffectOperator effectOp,
                [[maybe_unused]] int value) override
    {
        SetValue(entity, false);
    }

    void ApplyAura(T* entity, [[maybe_unused]] EffectOperator effectOp,
                   [[maybe_unused]] int value) override
    {
        AuraEffects* auraEffects = entity->auraEffects;
        if (auraEffects == nullptr)
        {
            auraEffects = new AuraEffects(entity->card->GetCardType());
            entity->auraEffects = auraEffects;
        }

        const int target = Attr<T>::GetAuraValue(auraEffects);
        Attr<T>::SetAuraValue(auraEffects, target + 1);
    }

    void RemoveAura(T* entity, [[maybe_unused]] EffectOperator effectOp,
                    [[maybe_unused]] int value) override
    {
        const int target = Attr<T>::GetAuraValue(entity->auraEffects);
        Attr<T>::SetAuraValue(entity->auraEffects, target - 1);
    }

 protected:
    virtual std::optional<bool>& GetRef(T* entity) = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ATTR_HPP
