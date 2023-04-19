// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SilenceTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SilenceTask::SilenceTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus SilenceTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (const auto minion = dynamic_cast<Minion*>(playable))
        {
            minion->Silence();
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SilenceTask::CloneImpl()
{
    return std::make_unique<SilenceTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
