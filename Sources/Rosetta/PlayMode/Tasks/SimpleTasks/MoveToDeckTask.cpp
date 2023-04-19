// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MoveToDeckTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
MoveToDeckTask::MoveToDeckTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus MoveToDeckTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        Playable* removedMinion = playable->zone->Remove(playable);
        removedMinion->Reset();

        if (removedMinion->player != player)
        {
            removedMinion->player = player;
            removedMinion->SetGameTag(GameTag::CONTROLLER, player->playerID);
        }

        Generic::ShuffleIntoDeck(player, m_source, playable);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MoveToDeckTask::CloneImpl()
{
    return std::make_unique<MoveToDeckTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
