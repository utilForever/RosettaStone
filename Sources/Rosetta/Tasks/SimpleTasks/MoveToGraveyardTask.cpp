// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MoveToGraveyardTask.hpp>

namespace RosettaStone::SimpleTasks
{
MoveToGraveyardTask::MoveToGraveyardTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskStatus MoveToGraveyardTask::Impl(Player* player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        entity->zone->Remove(*entity);
        entity->owner->GetGraveyardZone().Add(*entity);
    }

    return TaskStatus::COMPLETE;
}

ITask* MoveToGraveyardTask::CloneImpl()
{
    return new MoveToGraveyardTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
