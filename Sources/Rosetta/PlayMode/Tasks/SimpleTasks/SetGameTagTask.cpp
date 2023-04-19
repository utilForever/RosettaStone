// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetGameTagTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SetGameTagTask::SetGameTagTask(EntityType entityType, GameTag tag, int amount)
    : ITask(entityType), m_gameTag(tag), m_amount(amount)
{
    // Do nothing
}

TaskStatus SetGameTagTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->SetGameTag(m_gameTag, m_amount);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SetGameTagTask::CloneImpl()
{
    return std::make_unique<SetGameTagTask>(m_entityType, m_gameTag, m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
