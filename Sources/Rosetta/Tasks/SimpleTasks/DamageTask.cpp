// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
DamageTask::DamageTask(EntityType entityType, std::size_t damage,
                       bool isSpellDamage)
    : ITask(entityType), m_damage(damage), m_isSpellDamage(isSpellDamage)
{
    // Do nothing
}

TaskStatus DamageTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        const auto source = dynamic_cast<Playable*>(m_source);
        const auto character = dynamic_cast<Character*>(playable);

        Generic::TakeDamageToCharacter(
            source, character, static_cast<int>(m_damage), m_isSpellDamage);
    }

    return TaskStatus::COMPLETE;
}

ITask* DamageTask::CloneImpl()
{
    return new DamageTask(m_entityType, m_damage, m_isSpellDamage);
}
}  // namespace RosettaStone::SimpleTasks
