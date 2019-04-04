// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
ConditionTask::ConditionTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskID ConditionTask::GetTaskID() const
{
    return TaskID::CONDITION;
}

TaskStatus ConditionTask::Impl(Player& player)
{
    (void)player;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
