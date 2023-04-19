// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Actions/Generic.hpp>
#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
AddEnchantmentTask::AddEnchantmentTask(const std::string_view& cardID,
                                       EntityType entityType, bool useScriptTag)
    : m_cardID(cardID), m_entityType(entityType), m_useScriptTag(useScriptTag)
{
    // Do nothing
}

TaskStatus AddEnchantmentTask::Run(Player& player, Minion& source)
{
    int num = 0;
    if (m_useScriptTag)
    {
        num = player.taskStack.num;
    }

    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    Card enchantmentCard = Cards::FindCardByID(m_cardID);

    for (auto& minion : minions)
    {
        Generic::AddEnchantment(enchantmentCard, minion, num);
    }

    return TaskStatus::COMPLETE;
}

TaskStatus AddEnchantmentTask::Run(Player& player, Minion& source,
                                   Minion& target)
{
    auto minions =
        IncludeTask::GetMinions(m_entityType, player, source, target);
    Card enchantmentCard = Cards::FindCardByID(m_cardID);

    for (auto& minion : minions)
    {
        Generic::AddEnchantment(enchantmentCard, minion);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
