// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
AddEnchantmentTask::AddEnchantmentTask(std::string cardID,
                                       EntityType entityType)
    : ITask(entityType), m_cardID(std::move(cardID))
{
    // Do nothing
}

TaskID AddEnchantmentTask::GetTaskID() const
{
    return TaskID::ADD_ENCHANTMENT;
}

TaskStatus AddEnchantmentTask::Impl(Player& player)
{
    Card* enchantmentCard = Cards::FindCardByID(m_cardID);
    if (enchantmentCard->id.empty())
    {
        return TaskStatus::STOP;
    }

    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    Power power = enchantmentCard->power;

    for (auto& entity : entities)
    {
        const auto enchantment =
            Enchantment::GetInstance(player, enchantmentCard, entity);

        if (power.GetAura())
        {
            power.GetAura()->Activate(enchantment);
        }

        if (power.GetTrigger())
        {
            power.GetTrigger()->Activate(enchantment);
        }

        if (power.GetEnchant())
        {
            const auto& taskStack = player.GetGame()->taskStack;
            power.GetEnchant()->ActivateTo(entity, taskStack.num,
                                           taskStack.num1);
        }
    }

    return TaskStatus::COMPLETE;
}

ITask* AddEnchantmentTask::CloneImpl()
{
    return new AddEnchantmentTask(m_cardID, m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
