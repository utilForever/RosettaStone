// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
CountTask::CountTask(EntityType entityType, int numIndex,
                     std::vector<SelfCondition> conditions)
    : m_entityType(entityType),
      m_conditions(std::move(conditions)),
      m_numIndex(numIndex)
{
    // Do nothing
}

TaskStatus CountTask::Run(Player& player, Minion& source)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    int count = 0;

    if (m_conditions.empty())
    {
        count = static_cast<int>(minions.size());
    }
    else
    {
        for (auto& minion : minions)
        {
            bool flag = true;

            for (auto& condition : m_conditions)
            {
                if (!condition.Evaluate(minion))
                {
                    flag = false;
                }
            }

            if (flag)
            {
                ++count;
            }
        }
    }

    switch (m_numIndex)
    {
        case 0:
        player.taskStack.num = count;
            break;
        default:
            throw std::invalid_argument(
                "CountTask::Run() - Invalid number index");
    }

    return TaskStatus::COMPLETE;
}

TaskStatus CountTask::Run(Player& player, Minion& source,
                          [[maybe_unused]] Minion& target)
{
    auto minions = IncludeTask::GetMinions(m_entityType, player, source);
    int count = 0;

    if (m_conditions.empty())
    {
        count = static_cast<int>(minions.size());
    }
    else
    {
        for (auto& minion : minions)
        {
            bool flag = true;

            for (auto& condition : m_conditions)
            {
                if (!condition.Evaluate(minion))
                {
                    flag = false;
                }
            }

            if (flag)
            {
                ++count;
            }
        }
    }

    switch (m_numIndex)
    {
        case 0:
            player.taskStack.num = count;
            break;
        default:
            throw std::invalid_argument(
                "CountTask::Run() - Invalid number index");
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
