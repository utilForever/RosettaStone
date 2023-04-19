// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddAuraEffectTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
AddAuraEffectTask::AddAuraEffectTask(std::shared_ptr<IEffect> effect,
                                     EntityType entityType)
    : ITask(entityType), m_effect(std::move(effect))
{
    // Do nothing
}

TaskStatus AddAuraEffectTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        m_effect->ApplyAuraTo(playable);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AddAuraEffectTask::CloneImpl()
{
    return std::make_unique<AddAuraEffectTask>(m_effect, m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
