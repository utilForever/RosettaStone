// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/AddEnchantmentTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
AddEnchantmentTask::AddEnchantmentTask(const std::string_view& cardID,
                                       EntityType entityType)
    : m_cardID(cardID), m_entityType(entityType)
{
    // Do nothing
}

TaskStatus AddEnchantmentTask::Run(Player& player, Minion& source)
{
    return TaskStatus::COMPLETE;
}

TaskStatus AddEnchantmentTask::Run(Player& player, Minion& source,
                                   [[maybe_unused]] Minion& target)
{
    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
