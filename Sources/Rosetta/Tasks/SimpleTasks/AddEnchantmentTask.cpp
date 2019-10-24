// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
AddEnchantmentTask::AddEnchantmentTask(std::string cardID,
                                       EntityType entityType)
    : ITask(entityType), m_cardID(std::move(cardID))
{
    // Do nothing
}

TaskStatus AddEnchantmentTask::Impl(Player& player)
{
    Card* enchantmentCard = Cards::FindCardByID(m_cardID);
    if (enchantmentCard->id.empty())
    {
        return TaskStatus::STOP;
    }

    int num1 = 0, num2 = 0;

    if (m_entityType == EntityType::PLAYER)
    {
        Generic::AddEnchantment(enchantmentCard, m_source, &player, num1, num2);
        return TaskStatus::COMPLETE;
    }

    if (m_entityType == EntityType::ENEMY_PLAYER)
    {
        Generic::AddEnchantment(enchantmentCard, m_source, player.opponent,
                                num1, num2);
        return TaskStatus::COMPLETE;
    }

    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    Power power = enchantmentCard->power;

    for (auto& entity : entities)
    {
        Generic::AddEnchantment(enchantmentCard, m_source, entity, num1, num2);
    }

    return TaskStatus::COMPLETE;
}

ITask* AddEnchantmentTask::CloneImpl()
{
    return new AddEnchantmentTask(m_cardID, m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
