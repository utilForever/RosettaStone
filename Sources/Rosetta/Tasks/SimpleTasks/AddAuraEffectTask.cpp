// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/AddAuraEffectTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
AddAuraEffectTask::AddAuraEffectTask(std::shared_ptr<IEffect> effect,
                                     EntityType entityType)
    : ITask(entityType), m_effect(std::move(effect))
{
    // Do nothing
}

TaskStatus AddAuraEffectTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    for (auto& playable : playables)
    {
        m_effect->ApplyAuraTo(playable);
    }

    return TaskStatus::COMPLETE;
}

ITask* AddAuraEffectTask::CloneImpl()
{
    return new AddAuraEffectTask(m_effect, m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
