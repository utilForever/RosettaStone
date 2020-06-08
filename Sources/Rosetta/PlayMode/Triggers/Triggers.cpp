// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Enums/TaskEnums.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/PlayMode/Triggers/Triggers.hpp>

namespace RosettaStone::PlayMode
{
Trigger Triggers::EnrageTrigger(std::string&& enchantmentID)
{
    Trigger trigger(TriggerType::PREDAMAGE);
    trigger.triggerSource = TriggerSource::SELF;
    trigger.condition =
        std::make_shared<SelfCondition>(SelfCondition::IsUndamaged());
    trigger.tasks = { std::make_shared<SimpleTasks::AddEnchantmentTask>(
        std::move(enchantmentID), EntityType::SOURCE) };

    return trigger;
}
}  // namespace RosettaStone::PlayMode
