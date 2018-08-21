/*************************************************************************
> File Name: DestroyWeapon.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement DestroyWeapon
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/DestroyTask.h>

namespace Hearthstonepp::BasicTasks
{
DestroyTask::DestroyTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

TaskID DestroyTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyTask::Impl(Player& player1, Player& player2)
{
    if (m_entityType == +EntityType::OPPONENT_WEAPON)
    {
        player2.hero->weapon = nullptr;
        return MetaData::DESTROY_OPPONENT_WEAPON_SUCCESS;
    }

    else if (m_entityType == +EntityType::SOURCE || m_entityType == +EntityType::TARGET)
    {
        auto& field = m_entityType == +EntityType::SOURCE ? player1.field : player2.field;
        auto& entity = m_entityType == +EntityType::SOURCE ? source : target;

        auto ptr = std::find(field.begin(), field.end(), entity);
        if (ptr != field.end())
        {
            field.erase(ptr);
            return MetaData::DESTROY_MINION_SUCCESS;
        }
    }

    return MetaData::INVALID;
}
}  // namespace Hearthstonepp::BasicTasks