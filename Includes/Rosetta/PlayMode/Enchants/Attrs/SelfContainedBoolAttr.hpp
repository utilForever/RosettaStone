// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SELF_CONTAINED_BOOL_ATTR_HPP
#define ROSETTASTONE_PLAYMODE_SELF_CONTAINED_BOOL_ATTR_HPP

#include <Rosetta/PlayMode/Enchants/Attrs/BoolAttr.hpp>
#include <Rosetta/PlayMode/Enchants/GenericEffect.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief SelfContainedBoolAttr class.
//!
//! This class inherits from BoolAttr class and contains Effect() method
//! for generating generic effect using CRTP(Curiously Recurring Template
//! Pattern) technique.
//!
template <typename TargetT = Entity, typename SelfT>
class SelfContainedBoolAttr : public BoolAttr<TargetT>
{
 public:
    //! Default virtual destructor.
    virtual ~SelfContainedBoolAttr() = default;

    //! Generates new generic effect for boolean attribute.
    //! \param value The value of the generic effect.
    //! \return The generic effect that is dynamically allocated.
    static std::shared_ptr<GenericEffect<TargetT, SelfT>> Effect(
        bool value = true)
    {
        if (!m_singleton)
        {
            m_singleton = std::make_shared<SelfT>();
        }

        return std::make_shared<GenericEffect<TargetT, SelfT>>(
            m_singleton, EffectOperator::SET, value ? 1 : 0);
    }

 private:
    inline static std::shared_ptr<SelfT> m_singleton;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SELF_CONTAINED_BOOL_ATTR_HPP
