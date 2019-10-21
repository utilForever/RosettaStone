// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BOOL_ATTR_HPP
#define ROSETTASTONE_BOOL_ATTR_HPP

#include <Rosetta/Enchants/Attrs/Attr.hpp>

namespace RosettaStone
{
template <typename T = Entity>
class BoolAttr<T> : public Attr<T>
{
 public:
    virtual ~BoolAttr() = default;

    void Apply(T* entity, EffectOperator effectOp, int value) override
    {
        std::optional<int>& target = GetRef(entity);

        if (effectOp != EffectOperator::SET)
        {
            throw std::invalid_argument(
                "BoolAttr::Apply() - Invalid effect operator!");
        }

        target = value > 0;
    }

    void Remove(T* entity, [[maybe_unused]] EffectOperator effectOp,
                [[maybe_unused]] int value) override
    {
        std::optional<int>& target = GetRef(entity);

        target = false;
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

        ++Attr<T>::GetAuraRef(auraEffects);
    }

    void RemoveAura(T* entity, [[maybe_unused]] EffectOperator effectOp,
                    [[maybe_unused]] int value) override
    {
        --Attr<T>::GetAuraRef(entity->auraEffects);
    }

 protected:
    virtual std::optional<bool>& GetRef(T* entity) = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ATTR_HPP
