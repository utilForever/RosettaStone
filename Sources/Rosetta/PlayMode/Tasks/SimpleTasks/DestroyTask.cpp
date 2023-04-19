// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DestroyTask::DestroyTask(EntityType entityType, bool forceDeathPhase)
    : ITask(entityType), m_forceDeathPhase(forceDeathPhase)
{
    // Do nothing
}

TaskStatus DestroyTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->Destroy();
    }

    if (m_forceDeathPhase)
    {
        player->game->ProcessDestroyAndUpdateAura();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DestroyTask::CloneImpl()
{
    return std::make_unique<DestroyTask>(m_entityType, m_forceDeathPhase);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
