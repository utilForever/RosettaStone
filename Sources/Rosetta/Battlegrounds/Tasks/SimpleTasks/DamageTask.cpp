// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
DamageTask::DamageTask(EntityType entityType, int damage)
    : m_entityType(entityType), m_damage(damage)
{
    // Do nothing
}

TaskStatus DamageTask::Run(Player& player, [[maybe_unused]] Minion& source)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    for (auto& minion : minions)
    {
        minion.get().TakeDamage(m_damage);
    }

    return TaskStatus::COMPLETE;
}

TaskStatus DamageTask::Run(Player& player, [[maybe_unused]] Minion& source,
                           [[maybe_unused]] Minion& target)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    for (auto& minion : minions)
    {
        minion.get().TakeDamage(m_damage);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
