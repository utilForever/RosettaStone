// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Battle.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/AttackTask.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
AttackTask::AttackTask(EntityType attacker) : m_attacker(attacker)
{
    // Do nothing
}

TaskStatus AttackTask::Run(Player& player, Minion& source)
{
    Battle& battle = player.getBattleCallback();

    auto attackers = IncludeTask::GetMinions(m_attacker, player, source);
    for (auto& attacker : attackers)
    {
        Minion& battleTarget = battle.GetProperTarget(attacker);
        battleTarget.TakeDamage(attacker);
        attacker.get().TakeDamage(battleTarget);

        battle.ProcessDestroy(false);
    }

    return TaskStatus::COMPLETE;
}

TaskStatus AttackTask::Run(Player& player, Minion& source, Minion& target)
{
    Battle& battle = player.getBattleCallback();

    auto attackers =
        IncludeTask::GetMinions(m_attacker, player, source, target);
    for (auto& attacker : attackers)
    {
        Minion& battleTarget = battle.GetProperTarget(attacker);
        battleTarget.TakeDamage(attacker);
        attacker.get().TakeDamage(battleTarget);

        battle.ProcessDestroy(false);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
