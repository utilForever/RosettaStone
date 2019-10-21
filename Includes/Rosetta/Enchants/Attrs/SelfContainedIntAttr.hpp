// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SELF_CONTAINED_INT_ATTR_HPP
#define ROSETTASTONE_SELF_CONTAINED_INT_ATTR_HPP

#include <Rosetta/Enchants/Attrs/IntAttr.hpp>
#include <Rosetta/Enchants/GenericEffect.hpp>

namespace RosettaStone
{
template <typename SelfT, typename TargetT = Entity>
class SelfContainedIntAttr : public IntAttr<TargetT>
{
 public:
    virtual ~SelfContainedIntAttr() = default;

    static GenericEffect<TargetT, SelfT>* Effect(EffectOperator effectOp,
                                                 int value)
    {
        return new GenericEffect<TargetT, SelfT>(m_singleton, effectOp, value);
    }

 private:
    inline static SelfT* m_singleton = new SelfT();
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SELF_CONTAINED_INT_ATTR_HPP
