/*************************************************************************
> File Name: DestroyMinionTask.cpp
> Project Name: Hearthstonepp
> Author: SeungHyun Jeon
> Purpose: Implement DestroyMinion
> Created Time: 2018/08/21
> Copyright (c) 2018, SeungHyun Jeon
*************************************************************************/
#include <Cards/Character.h>
#include <Tasks/BasicTasks/DestroyMinionTask.h>

namespace Hearthstonepp::BasicTasks
{
DestroyMinionTask::DestroyMinionTask(Player& player, Character* character) : m_player(player), m_character(character)
{
    // Do nothing
}

TaskID DestroyMinionTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyMinionTask::Impl(Player &, Player &)
{
    auto& field = m_player.field;

    auto ptr = std::find(field.begin(), field.end(), m_character);
    if (ptr != field.end())
    {
        field.erase(ptr);
        return MetaData::DESTROY_MINION_SUCCESS;
    }

    return MetaData::INVALID;
}
}
