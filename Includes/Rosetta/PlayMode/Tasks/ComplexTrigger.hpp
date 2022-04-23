// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_COMPLEX_TRIGGER_HPP
#define ROSETTASTONE_PLAYMODE_COMPLEX_TRIGGER_HPP

#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;

//!
//! \brief ComplexTrigger class.
//!
//! This class lists complex triggers such as "If you played a Naga
//! while holding this.".
//!
class ComplexTrigger
{
 public:
    //! Adds a trigger for checking "If you played a Naga while holding this".
    //! \param power A power to add the trigger.
    static void PlayedNagaWhileHoldingThis(Power& power)
    {
        power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
        power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
        power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
        power.GetTrigger()->conditions = SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::NAGA))
        };
        power.GetTrigger()->tasks = {
            std::make_shared<SimpleTasks::SetGameTagTask>(
                EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1, 1)
        };
    }

    //! Adds a trigger for checking "If you cast a spell while holding this".
    //! \param power A power to add the trigger.
    static void CastSpellWhileHoldingThis(Power& power)
    {
        power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));
        power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
        power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
        power.GetTrigger()->tasks = {
            std::make_shared<SimpleTasks::SetGameTagTask>(
                EntityType::SOURCE, GameTag::TAG_SCRIPT_DATA_NUM_1, 1)
        };
    }
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_COMPLEX_TRIGGER_HPP
