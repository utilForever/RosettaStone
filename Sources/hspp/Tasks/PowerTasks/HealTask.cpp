// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PowerTasks/HealTask.h>

namespace Hearthstonepp::PowerTask
{
HealTask::HealTask(EntityType entityType, int amount)
    : m_entityType(entityType), m_amount(amount)
{
    // Do nothing
}

TaskID HealTask::GetTaskID() const
{
    return TaskID::HEAL;
}

MetaData HealTask::Impl(Player& player)
{
    if (m_entityType == +EntityType::HERO)
    {
        if (player.hero->health + m_amount <= player.hero->maxHealth)
        {
            player.hero->health += m_amount;
        }
        else
        {
            player.hero->health = player.hero->maxHealth;
        }

        return MetaData::HEAL_SUCCESS;
    }

    return MetaData::HEAL_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask