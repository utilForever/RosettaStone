// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>

namespace RosettaStone::SimpleTasks
{
TaskID RemoveEnchantmentTask::GetTaskID() const
{
    return TaskID::REMOVE_ENCHANTMENT;
}

TaskStatus RemoveEnchantmentTask::Impl(Player& player)
{
    auto enchantment = dynamic_cast<Enchantment*>(m_source);
    if (enchantment == nullptr)
    {
        return TaskStatus::STOP;
    }

    if (enchantment->card->power.GetEnchant() != nullptr)
    {
        for (auto& effect : enchantment->card->power.GetEnchant()->effects)
        {
            effect->Remove(m_target);
        }
    }

    if (auto aura = enchantment->card->power.GetAura(); aura != nullptr)
    {
        m_source->onGoingEffect->Remove();
    }

    enchantment->Remove();

    return TaskStatus::COMPLETE;
}

ITask* RemoveEnchantmentTask::CloneImpl()
{
    return new RemoveEnchantmentTask();
}
}  // namespace RosettaStone::SimpleTasks
