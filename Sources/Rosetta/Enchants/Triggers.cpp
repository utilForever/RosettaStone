// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Enchants/Triggers.hpp>
#include <Rosetta/Enums/TaskEnums.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>

namespace RosettaStone
{
Trigger Triggers::EnrageTrigger(std::string&& enchantmentID)
{
    Trigger trigger(TriggerType::PREDAMAGE);
    trigger.triggerSource = TriggerSource::SELF;
    trigger.condition = new SelfCondition(SelfCondition::IsUndamaged());
    trigger.tasks = { std::make_shared<SimpleTasks::AddEnchantmentTask>(
        std::move(enchantmentID), EntityType::SOURCE) };

    return trigger;
}
}  // namespace RosettaStone
