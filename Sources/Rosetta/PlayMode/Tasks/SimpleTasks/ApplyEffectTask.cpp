// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/ApplyEffectTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
ApplyEffectTask::ApplyEffectTask(EntityType entityType,
                                 std::vector<std::shared_ptr<IEffect>> effects)
    : ITask(entityType), m_effects(std::move(effects))
{
    // Do nothing
}

TaskStatus ApplyEffectTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        for (const auto& effect : m_effects)
        {
            effect->ApplyTo(playable);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ApplyEffectTask::CloneImpl()
{
    return std::make_unique<ApplyEffectTask>(m_entityType, m_effects);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
