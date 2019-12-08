// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
DamageNumberTask::DamageNumberTask(EntityType entityType, bool isSpellDamage)
    : ITask(entityType), m_isSpellDamage(isSpellDamage)
{
    // Do nothing
}

TaskStatus DamageNumberTask::Impl(Player* player)
{
    const int damage = m_source->game->taskStack.num[0];
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        const auto character = dynamic_cast<Character*>(playable);
        Generic::TakeDamageToCharacter(dynamic_cast<Playable*>(m_source),
                                       character, damage, m_isSpellDamage);
    }

    return TaskStatus::COMPLETE;
}

ITask* DamageNumberTask::CloneImpl()
{
    return new DamageNumberTask(m_entityType, m_isSpellDamage);
}
}  // namespace RosettaStone::SimpleTasks
