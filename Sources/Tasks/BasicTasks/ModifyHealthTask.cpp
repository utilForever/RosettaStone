/*************************************************************************
> File Name: ModifyHealth.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement ModifyHealthTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/ModifyHealthTask.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
ModifyHealthTask::ModifyHealthTask(Character* character, BYTE damage)
    : m_character(character), m_damage(damage)
{
    // Do Nothing
}

TaskID ModifyHealthTask::GetTaskID() const
{
    return TaskID::MODIFY_HEALTH;
}

MetaData ModifyHealthTask::Impl(Player&, Player&)
{
    if (m_character->gameTags[+GameTag::DIVINE_SHIELD] == 1)
    {
        m_damage = 0;
    }

    int remainHealth = static_cast<int>(m_character->health) - m_damage;

    // if minion is exhausted
    if (remainHealth <= 0)
    {
        remainHealth = 0;
    }

    // adjust health
    m_character->health = static_cast<size_t>(remainHealth);

    return MetaData::MODIFY_HEALTH_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks