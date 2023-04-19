// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/SetGameTagTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
SetGameTagTask::SetGameTagTask(EntityType entityType, GameTag tag, int amount)
    : m_entityType(entityType), m_gameTag(tag), m_amount(amount)
{
    // Do nothing
}

TaskStatus SetGameTagTask::Run(Player& player, Minion& source)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);

    for (auto& minion : minions)
    {
        minion.get().SetGameTag(m_gameTag, m_amount);
    }

    return TaskStatus::COMPLETE;
}

TaskStatus SetGameTagTask::Run(Player& player, Minion& source, Minion& target)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);

    for (auto& minion : minions)
    {
        minion.get().SetGameTag(m_gameTag, m_amount);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
