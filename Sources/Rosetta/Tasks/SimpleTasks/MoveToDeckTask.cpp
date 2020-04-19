// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MoveToDeckTask.hpp>

namespace RosettaStone::SimpleTasks
{
MoveToDeckTask::MoveToDeckTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus MoveToDeckTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->zone->Remove(playable);

        Generic::ShuffleIntoDeck(player, m_source, playable);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MoveToDeckTask::CloneImpl()
{
    return std::make_unique<MoveToDeckTask>(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
