// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
GetGameTagTask::GetGameTagTask(EntityType entityType, GameTag tag,
                               int minionIndex)
    : m_entityType(entityType), m_gameTag(tag), m_minionIndex(minionIndex)
{
    // Do nothing
}

TaskStatus GetGameTagTask::Run(Player& player, Minion& source)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    if (minions.empty())
    {
        return TaskStatus::STOP;
    }

    const int value = minions[m_minionIndex].get().GetGameTag(m_gameTag);
    player.taskStack.num = value;

    return TaskStatus::COMPLETE;
}

TaskStatus GetGameTagTask::Run(Player& player, Minion& source, Minion& target)
{
    auto minions =
        IncludeTask::GetMinions(m_entityType, player, source, target);
    if (minions.empty())
    {
        return TaskStatus::STOP;
    }

    const int value = minions[m_minionIndex].get().GetGameTag(m_gameTag);
    player.taskStack.num = value;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
