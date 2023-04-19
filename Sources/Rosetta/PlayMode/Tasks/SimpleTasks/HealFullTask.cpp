// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/HealFullTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
HealFullTask::HealFullTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus HealFullTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        const auto character = dynamic_cast<Character*>(playable);
        character->TakeFullHeal(dynamic_cast<Playable*>(m_source));
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> HealFullTask::CloneImpl()
{
    return std::make_unique<HealFullTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
