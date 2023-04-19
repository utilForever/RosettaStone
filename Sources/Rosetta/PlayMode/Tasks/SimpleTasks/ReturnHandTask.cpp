// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ReturnHandTask.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
ReturnHandTask::ReturnHandTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus ReturnHandTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (playable->player->GetHandZone()->IsFull())
        {
            playable->Destroy();
        }
        else
        {
            playable->zone->Remove(playable);
            playable->Reset();

            Generic::AddCardToHand(playable->player, playable);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ReturnHandTask::CloneImpl()
{
    return std::make_unique<ReturnHandTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
