// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ATTR_HPP
#define ROSETTASTONE_ATTR_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone
{
template <typename T = Entity>
class Attr<T>
{
 public:
    virtual ~Attr() = default;

    virtual void Apply(T* entity, EffectOperator effectOp, int value) = 0;

    virtual void Remove(T* entity, EffectOperator effectOp, int value) = 0;

    virtual void ApplyAura(T* entity, EffectOperator effectOp, int value) = 0;

    virtual void RemoveAura(T* entity, EffectOperator effectOp, int value) = 0;

 protected:
    virtual int& GetAuraRef(AuraEffects* auraEffects) = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ATTR_HPP
