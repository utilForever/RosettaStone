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
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;

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
        trigger.conditions = SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsUndamaged()) };
        trigger.tasks = { std::make_shared<SimpleTasks::AddEnchantmentTask>(
            std::move(enchantmentID), EntityType::SOURCE) };

        return trigger;
    }

    //! Trigger for rank spells.
    //! \param mana The amount of mana requires for upgrade.
    //! \param enchantmentID The upgraded card ID.
    static Trigger RankSpellTrigger(int mana, std::string&& upgradedCardID)
    {
        Trigger trigger(TriggerType::MANA_CRYSTAL);
        trigger.triggerActivation = TriggerActivation::HAND;
        trigger.conditions = SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::HasAtLeastManaCrystal(mana)) };
        trigger.tasks = { std::make_shared<SimpleTasks::ChangeEntityTask>(
            std::move(upgradedCardID)) };

        return trigger;
    }
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TRIGGERS_HPP