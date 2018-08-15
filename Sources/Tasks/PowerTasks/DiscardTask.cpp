/*************************************************************************
> File Name: DiscardTask.cpp
> Project Name: Hearthstonepp
> Author: Sungkuk Park
> Purpose: Implement DiscardTask
> Created Time: 2018/08/15
> Copyright (c) 2018, Sungkuk Park
*************************************************************************/
#include <Tasks/PowerTasks/DiscardTask.h>
#include <random>

namespace Hearthstonepp::PowerTask
{
DiscardTask::DiscardTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

TaskID DiscardTask::GetTaskID() const
{
    return TaskID::DISCARD;
}

MetaData DiscardTask::Impl(Player& player1, Player&)
{
    if (m_entityType == +EntityType::MY_HAND)
    {
        if (player1.hand.size() <= 0)
        {
            return MetaData::DISCARD_MY_HAND_SUCCESS;
        }

        std::random_device rd;
        std::uniform_int_distribution<size_t> dist(0, player1.hand.size() - 1);

        size_t discardIdx = dist(rd);

        // Card Hand Index Verification
        if (discardIdx >= player1.hand.size())
        {
            return MetaData::DISCARD_IDX_OUT_OF_RANGE;
        }

        player1.hand.erase(player1.hand.begin() + discardIdx);
        return MetaData::DISCARD_MY_HAND_SUCCESS;
    }

    return MetaData::INVALID;
}
}  // namespace Hearthstonepp::PowerTask