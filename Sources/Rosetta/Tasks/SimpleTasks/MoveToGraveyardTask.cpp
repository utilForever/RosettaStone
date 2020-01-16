// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MoveToGraveyardTask.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>

namespace RosettaStone::SimpleTasks
{
MoveToGraveyardTask::MoveToGraveyardTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskStatus MoveToGraveyardTask::Impl(Player* player)
{
    auto playables =
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

ITask* MoveToGraveyardTask::CloneImpl()
{
    return new MoveToGraveyardTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
