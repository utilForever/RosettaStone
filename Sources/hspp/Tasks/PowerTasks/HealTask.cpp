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

MetaData HealTask::Impl(Player& player1, Player&)
{
    if (m_entityType == +EntityType::HERO)
    {
        if (player1.hero->health + m_amount <= player1.hero->maxHealth)
        {
            player1.hero->health += m_amount;
        }
        else
        {
            player1.hero->health = player1.hero->maxHealth;
        }

        return MetaData::HEAL_SUCCESS;
    }

    return MetaData::HEAL_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask