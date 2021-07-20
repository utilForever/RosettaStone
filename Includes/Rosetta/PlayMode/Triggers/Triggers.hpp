// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_TRIGGERS_HPP
#define ROSETTASTONE_PLAYMODE_TRIGGERS_HPP

#include <Rosetta/PlayMode/Triggers/Trigger.hpp>

#include <string>

namespace RosettaStone::PlayMode
{
//!
//! \brief Triggers class.
//!
//! This class includes utility methods for trigger.
//!
class Triggers
{
 public:
    //! Trigger for enrage.
    //! \param enchantmentID The card ID of enchantment.
    static Trigger EnrageTrigger(std::string&& enchantmentID)
    {
        Trigger trigger(TriggerType::PREDAMAGE);
        trigger.triggerSource = TriggerSource::SELF;
        trigger.condition =
            std::make_shared<SelfCondition>(SelfCondition::IsUndamaged());
        trigger.tasks = { std::make_shared<SimpleTasks::AddEnchantmentTask>(
            std::move(enchantmentID), EntityType::SOURCE) };

        return trigger;
    }
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TRIGGERS_HPP