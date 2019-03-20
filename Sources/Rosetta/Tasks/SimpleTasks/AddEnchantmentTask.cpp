// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>

namespace RosettaStone::SimpleTasks
{
AddEnchantmentTask::AddEnchantmentTask(std::string&& cardID,
                                       EntityType entityType)
    : ITask(entityType), m_cardID(cardID)
{
    // Do nothing
}

TaskID AddEnchantmentTask::GetTaskID() const
{
    return TaskID::ADD_ENCHANTMENT;
}

TaskStatus AddEnchantmentTask::Impl(Player&)
{
    Card enchantmentCard = Cards::GetInstance().FindCardByID(m_cardID);
    if (enchantmentCard.id.empty())
    {
        return TaskStatus::STOP;
    }

    Power power = Cards::GetInstance().FindCardByID(m_cardID).power;
    power.GetEnchant().ActivateTo(dynamic_cast<Character*>(m_target));

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
