// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/DamageTask.hpp>

namespace Hearthstonepp::BasicTasks
{
DamageTask::DamageTask(Character* character, size_t damage)
    : m_character(character), m_damage(damage)
{
    // Do Nothing
}

TaskID DamageTask::GetTaskID() const
{
    return TaskID::MODIFY_HEALTH;
}

MetaData DamageTask::Impl(Player&)
{
    if (m_character->GetGameTag(GameTag::DIVINE_SHIELD) == 1)
    {
        m_damage = 0;
    }

    const int remainHealth =
        static_cast<int>(m_character->health) - static_cast<int>(m_damage);
    m_character->health =
        remainHealth > 0 ? static_cast<size_t>(remainHealth) : 0u;

    return MetaData::MODIFY_HEALTH_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
