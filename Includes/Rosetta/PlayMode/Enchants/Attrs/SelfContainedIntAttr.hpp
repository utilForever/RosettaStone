// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SELF_CONTAINED_INT_ATTR_HPP
#define ROSETTASTONE_PLAYMODE_SELF_CONTAINED_INT_ATTR_HPP

#include <Rosetta/PlayMode/Enchants/Attrs/IntAttr.hpp>
#include <Rosetta/PlayMode/Enchants/GenericEffect.hpp>

#include <memory>

namespace RosettaStone::PlayMode
{
//!
//! \brief SelfContainedIntAttr class.
//!
//! This class inherits from IntAttr class and contains Effect() method
//! for generating generic effect using CRTP(Curiously Recurring Template
//! Pattern) technique.
//!
template <typename SelfT, typename TargetT = Entity>
class SelfContainedIntAttr : public IntAttr<TargetT>
{
 public:
    //! Default virtual destructor.
    virtual ~SelfContainedIntAttr() = default;

    //! Generates new generic effect for integer attribute.
    //! \param effectOp The effect operator of the generic effect.
    //! \param value The value of the generic effect.
    //! \return The generic effect that is dynamically allocated.
    static std::shared_ptr<GenericEffect<TargetT, SelfT>> Effect(
        EffectOperator effectOp, int value)
    {
        if (!m_singleton)
        {
            m_singleton = std::make_shared<SelfT>();
        }

        return std::make_shared<GenericEffect<TargetT, SelfT>>(m_singleton,
                                                               effectOp, value);
    }

 private:
    inline static std::shared_ptr<SelfT> m_singleton;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SELF_CONTAINED_INT_ATTR_HPP
