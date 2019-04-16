// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ReturnHandTask.hpp>

namespace RosettaStone::SimpleTasks
{
ReturnHandTask::ReturnHandTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskID ReturnHandTask::GetTaskID() const
{
    return TaskID::RETURN_HAND;
}

TaskStatus ReturnHandTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        Generic::RemoveMinionFromField(entity->GetOwner(),
                                       dynamic_cast<Minion*>(entity));
        entity->Reset();
        Generic::AddCardToHand(entity->GetOwner(), entity);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
