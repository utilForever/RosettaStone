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

MetaData ModifyHealthTask::Impl(Player& user, Player&)
{
    int hurted = static_cast<int>(m_character->health) - m_damage;

    // if minion is exhausted
    if (hurted <= 0)
    {
        hurted = 0;
        user.usedMinion.emplace_back(m_character);

        // find minion and remove it from field
        auto& field = user.field;
        auto ptr = std::find(field.begin(), field.end(), m_character);
        if (ptr != field.end())
        {
            *ptr = nullptr;
            field.erase(ptr);
        }
    }

    // adjust health
    m_character->health = static_cast<size_t>(hurted);
    return MetaData::MODIFY_HEALTH_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks