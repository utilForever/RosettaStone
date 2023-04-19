// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/RandomTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::Battlegrounds::SimpleTasks
{
RandomTask::RandomTask(EntityType entityType, int amount)
    : m_entityType(entityType), m_amount(amount)
{
    // Do nothing
}

TaskStatus RandomTask::Run(Player& player, Minion& source)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    if (minions.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_amount == 1)
    {
        const auto idx = Random::get<std::size_t>(0, minions.size() - 1);
        player.taskStack.minions =
            std::vector<std::reference_wrapper<Minion>>{ minions.at(idx) };
    }

    return TaskStatus::COMPLETE;
}

TaskStatus RandomTask::Run(Player& player, Minion& source,
                           [[maybe_unused]] Minion& target)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    if (minions.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_amount == 1)
    {
        const auto idx = Random::get<std::size_t>(0, minions.size() - 1);
        player.taskStack.minions =
            std::vector<std::reference_wrapper<Minion>>{ minions.at(idx) };
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
