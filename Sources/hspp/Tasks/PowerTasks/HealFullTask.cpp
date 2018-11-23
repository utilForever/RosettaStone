// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PowerTasks/HealFullTask.h>

namespace Hearthstonepp::PowerTask
{
HealFullTask::HealFullTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

TaskID HealFullTask::GetTaskID() const
{
    return TaskID::HEAL_FULL;
}

MetaData HealFullTask::Impl(Player&)
{
    const auto character = dynamic_cast<Character*>(m_target);
    character->health = character->maxHealth;

    return MetaData::HEAL_FULL_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask