// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MoveToGraveyardTask.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
MoveToGraveyardTask::MoveToGraveyardTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskStatus MoveToGraveyardTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->zone->Remove(playable);
        playable->player->GetGraveyardZone()->Add(playable);

        if (playable->card->IsSecret() &&
            playable->GetGameTag(GameTag::REVEALED) == 1)
        {
            player->game->triggerManager.OnSecretRevealedTrigger(playable);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MoveToGraveyardTask::CloneImpl()
{
    return std::make_unique<MoveToGraveyardTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
