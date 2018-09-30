// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PowerTasks/FreezeTask.h>

namespace Hearthstonepp::PowerTask
{
FreezeTask::FreezeTask(EntityType entityType, int turn)
    : m_entityType(entityType), m_turn(turn)
{
    // Do nothing
}

TaskID FreezeTask::GetTaskID() const
{
    return TaskID::FREEZE;
}

MetaData FreezeTask::Impl(Player&, Player&)
{
    target->gameTags[+GameTag::FROZEN] = m_turn;
    target->attackableCount = 0;

    return MetaData::FREEZE_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask