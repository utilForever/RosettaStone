// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SELF_CONTAINED_BOOL_ATTR_HPP
#define ROSETTASTONE_SELF_CONTAINED_BOOL_ATTR_HPP

#include <Rosetta/Enchants/Attrs/BoolAttr.hpp>
#include <Rosetta/Enchants/GenericEffect.hpp>

namespace RosettaStone
{
template <typename TargetT = Entity, typename SelfT>
class SelfContainedBoolAttr : public BoolAttr<TargetT>
{
 public:
    virtual ~SelfContainedBoolAttr() = default;

    static GenericEffect<TargetT, SelfT>* Effect(bool value = true)
    {
        return new GenericEffect<TargetT, SelfT>(
            m_singleton, EffectOperator::SET, value ? 1 : 0);
    }

 private:
    SelfT* m_singleton = new SelfT();
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SELF_CONTAINED_BOOL_ATTR_HPP
