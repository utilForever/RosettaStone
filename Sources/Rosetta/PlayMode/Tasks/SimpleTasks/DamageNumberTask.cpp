// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DamageNumberTask::DamageNumberTask(EntityType entityType, bool isSpellDamage)
    : ITask(entityType), m_isSpellDamage(isSpellDamage)
{
    // Do nothing
}

TaskStatus DamageNumberTask::Impl(Player* player)
{
    const int damage = m_source->game->taskStack.num[0];
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (const auto character = dynamic_cast<Character*>(playable);
            character)
        {
            Generic::TakeDamageToCharacter(dynamic_cast<Playable*>(m_source),
                                           character, damage, m_isSpellDamage);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DamageNumberTask::CloneImpl()
{
    return std::make_unique<DamageNumberTask>(m_entityType, m_isSpellDamage);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
