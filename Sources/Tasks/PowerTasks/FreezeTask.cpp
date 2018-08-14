/*************************************************************************
> File Name: FreezeTask.cpp
> Project Name: Hearthstonepp
> Author: Seung-Hyun Jeon
> Purpose: Implement Freeze
> Created Time: 2018/08/14
> Copyright (c) 2018, Seung-Hyun Jeon
*************************************************************************/
#include <Tasks/PowerTasks/FreezeTask.h>

namespace Hearthstonepp::PowerTask
{
    FreezeTask::FreezeTask(Character* target, int turn): m_target(target), m_turn(turn)
    {
        // Do nothing
    }

    TaskID FreezeTask::GetTaskID() const
    {
        return TaskID::FREEZE;
    }

    MetaData FreezeTask::Impl(Player&, Player&)
    {
        m_target->gameTags[+GameTag::FROZEN] = m_turn;
        m_target->attackableCount = 0;

        return MetaData::FREEZE_SUCCESS;
    }
}  // namespace Hearthstonepp::PowerTask



