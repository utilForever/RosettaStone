// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
IncludeTask::IncludeTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

std::vector<std::reference_wrapper<Minion>> IncludeTask::GetMinions(
    EntityType entityType, Player& player, Minion& source)
{
    std::vector<std::reference_wrapper<Minion>> minions;

    switch (entityType)
    {
        case EntityType::SOURCE:
            minions.emplace_back(source);
            break;
        case EntityType::TARGET:
            break;
        case EntityType::MINIONS:
            player.GetField().ForEachAlive([&](MinionData& minion) {
                minions.emplace_back(minion.value());
            });
            break;
        case EntityType::MINIONS_NOSOURCE:
            player.GetField().ForEachAlive([&](MinionData& minion) {
                if (minion.value().GetPoolIndex() != source.GetPoolIndex())
                {
                    minions.emplace_back(minion.value());
                }
            });
            break;
        case EntityType::ENEMY_MINIONS:
        {
            Player& opponent = player.getOpponentPlayerCallback(player);
            opponent.GetField().ForEachAlive([&](MinionData& minion) {
                minions.emplace_back(minion.value());
            });
        }
        break;
        case EntityType::STACK:
            minions = player.taskStack.minions;
            break;
        default:
            throw std::invalid_argument(
                "IncludeTask::GetEntities() - Invalid entity type");
    }

    return minions;
}

std::vector<std::reference_wrapper<Minion>> IncludeTask::GetMinions(
    EntityType entityType, [[maybe_unused]] Player& player,
    [[maybe_unused]] Minion& source, Minion& target)
{
    std::vector<std::reference_wrapper<Minion>> minions;

    switch (entityType)
    {
        case EntityType::TARGET:
            minions.emplace_back(target);
            break;
        default:
            throw std::invalid_argument(
                "IncludeTask::GetEntities() - Invalid entity type");
    }

    return minions;
}

TaskStatus IncludeTask::Run(Player& player, Minion& source)
{
    const auto minions = GetMinions(m_entityType, player, source);
    player.taskStack.minions = minions;

    return TaskStatus::COMPLETE;
}

TaskStatus IncludeTask::Run(Player& player, Minion& source, Minion& target)
{
    const auto minions = GetMinions(m_entityType, player, source, target);
    player.taskStack.minions = minions;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
