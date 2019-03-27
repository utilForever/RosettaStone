// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/HealFullTask.hpp>

namespace RosettaStone::SimpleTasks
{
HealFullTask::HealFullTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskID HealFullTask::GetTaskID() const
{
    return TaskID::HEAL_FULL;
}

TaskStatus HealFullTask::Impl(Player&)
{
    const auto character = dynamic_cast<Character*>(m_target);
    character->health = character->maxHealth;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
