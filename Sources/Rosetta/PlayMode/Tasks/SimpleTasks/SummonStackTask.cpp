// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonStackTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SummonStackTask::SummonStackTask(bool removeFromZone)
    : m_removeFromZone(removeFromZone)
{
    // Do nothing
}

TaskStatus SummonStackTask::Impl(Player* player)
{
    const auto stack = player->game->taskStack;

    if (player->GetFieldZone()->IsFull() || stack.playables.empty())
    {
        return TaskStatus::STOP;
    }

    for (const auto& playable : stack.playables)
    {
        if (playable->player->GetFieldZone()->IsFull())
        {
            continue;
        }

        if (m_removeFromZone)
        {
            playable->zone->Remove(playable);
        }

        Generic::Summon(dynamic_cast<Minion*>(playable), -1, m_source);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SummonStackTask::CloneImpl()
{
    return std::make_unique<SummonStackTask>(m_removeFromZone);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
