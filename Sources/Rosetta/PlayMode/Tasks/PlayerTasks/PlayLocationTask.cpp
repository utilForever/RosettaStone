// Copyright (c) 2026 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayLocationTask.hpp>

#include <algorithm>

namespace RosettaStone::PlayMode::PlayerTasks
{
PlayLocationTask::PlayLocationTask(Entity* source, Playable* target)
    : ITask(source, target)
{
    // Do nothing
}

TaskStatus PlayLocationTask::Impl(Player* player)
{
    const auto location = dynamic_cast<Location*>(m_source);
    const auto target = dynamic_cast<Character*>(m_target);

    if (!location || location->player != player ||
        location->GetZoneType() != ZoneType::PLAY ||
        !location->IsPlayableByPlayer() ||
        !location->IsValidPlayTarget(target) ||
        (m_target && (!target || !std::ranges::contains(
                                     location->GetValidPlayTargets(), target))))
    {
        return TaskStatus::STOP;
    }

    player->game->currentEventData =
        std::make_unique<EventMetaData>(location, target);

    if (target)
    {
        location->SetCardTarget(target->GetGameTag(GameTag::ENTITY_ID));
        Trigger::ValidateTriggers(player->game, location, SequenceType::TARGET);

        player->game->taskQueue.StartEvent();
        player->game->triggerManager.OnTargetTrigger(location);
        player->game->ProcessTasks();
        player->game->taskQueue.EndEvent();
    }

    player->game->taskQueue.StartEvent();
    location->ActivateTask(PowerType::POWER, target);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();

    if (!location->isDestroyed)
    {
        location->Use();
        player->game->ProcessDestroyAndUpdateAura();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> PlayLocationTask::CloneImpl()
{
    return std::make_unique<PlayLocationTask>(m_source, m_target);
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
