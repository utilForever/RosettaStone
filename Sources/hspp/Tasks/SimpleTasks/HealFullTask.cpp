// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/HealFullTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
HealFullTask::HealFullTask(EntityType entityType) : m_entityType(entityType)
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

    return TaskStatus::HEAL_FULL_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks