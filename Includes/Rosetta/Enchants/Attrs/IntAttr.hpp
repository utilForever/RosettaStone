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
    virtual ~IntAttr() = default;

    void Apply(T* entity, EffectOperator effectOp, int value) override
    {
    }

    void ApplyAura(T* entity, EffectOperator effectOp, int value) override
    {
    }

    void Remove(T* entity, EffectOperator effectOp, int value) override
    {
    }

    void RemoveAura(T* entity, EffectOperator effectOp, int value) override
    {
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ATTR_HPP
