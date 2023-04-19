// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/DamageHeroTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
DamageHeroTask::DamageHeroTask(int damage) : m_damage(damage)
{
    // Do nothing
}

TaskStatus DamageHeroTask::Run(Player& player, [[maybe_unused]] Minion& source)
{
    player.hero.TakeDamage(player, m_damage);

    return TaskStatus::COMPLETE;
}

TaskStatus DamageHeroTask::Run(Player& player, [[maybe_unused]] Minion& source,
                               [[maybe_unused]] Minion& target)
{
    player.hero.TakeDamage(player, m_damage);

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
