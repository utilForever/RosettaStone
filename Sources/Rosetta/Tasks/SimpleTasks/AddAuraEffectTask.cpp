// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/AddAuraEffectTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
AddAuraEffectTask::AddAuraEffectTask(Effect effect, EntityType entityType)
    : ITask(entityType), m_effect(effect)
{
    // Do nothing
}

TaskID AddAuraEffectTask::GetTaskID() const
{
    return TaskID::ADD_AURA_EFFECT;
}

TaskStatus AddAuraEffectTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    for (auto& entity : entities)
    {
        m_effect.Apply(*entity->auraEffects);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
