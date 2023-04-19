// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/ReduceTavernCostTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
ReduceTavernCostTask::ReduceTavernCostTask(TavernButton button, int cost)
    : m_tavernButton(button), m_cost(cost)
{
    // Do nothing
}

TaskStatus ReduceTavernCostTask::Run(Player& player,
                                     [[maybe_unused]] Minion& source)
{
    if (m_tavernButton == TavernButton::UPGRADE)
    {
        player.coinToUpgradeTavern -= m_cost;

        if (player.coinToUpgradeTavern < 0)
        {
            player.coinToUpgradeTavern = 0;
        }
    }

    return TaskStatus::COMPLETE;
}

TaskStatus ReduceTavernCostTask::Run(Player& player,
                                     [[maybe_unused]] Minion& source,
                                     [[maybe_unused]] Minion& target)
{
    if (m_tavernButton == TavernButton::UPGRADE)
    {
        player.coinToUpgradeTavern -= m_cost;

        if (player.coinToUpgradeTavern < 0)
        {
            player.coinToUpgradeTavern = 0;
        }
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
