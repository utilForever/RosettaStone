// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/DamageTask.hpp>

namespace Hearthstonepp::SimpleTasks
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
}  // namespace Hearthstonepp::SimpleTasks