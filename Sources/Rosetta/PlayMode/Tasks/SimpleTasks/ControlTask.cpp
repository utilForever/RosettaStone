// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
ControlTask::ControlTask(EntityType entityType, bool opposite)
    : ITask(entityType), m_opposite(opposite)
{
    // Do nothing
}

TaskStatus ControlTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (playable->GetZoneType() != ZoneType::PLAY)
        {
            continue;
        }

        if ((!m_opposite && player->GetFieldZone()->IsFull()) ||
            (m_opposite && player->opponent->GetFieldZone()->IsFull()))
        {
            playable->Destroy();
            continue;
        }

        const auto removedMinion =
            dynamic_cast<Minion*>(playable->zone->Remove(playable));
        removedMinion->game->UpdateAura();
        removedMinion->player = m_opposite ? player->opponent : player;

        removedMinion->player->GetFieldZone()->Add(removedMinion);
        if (removedMinion->HasCharge())
        {
            removedMinion->SetExhausted(false);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ControlTask::CloneImpl()
{
    return std::make_unique<ControlTask>(m_entityType, m_opposite);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
