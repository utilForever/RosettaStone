// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PowerTasks/FreezeTask.h>

namespace Hearthstonepp::PowerTask
{
FreezeTask::FreezeTask(Character* source, Character* target)
    : m_source(source), m_target(target)
{
    // Do nothing
}

TaskID FreezeTask::GetTaskID() const
{
    return TaskID::FREEZE;
}

MetaData FreezeTask::Impl(Player&, Player&)
{
    m_target->gameTags[+GameTag::FROZEN] = 1;

    return MetaData::FREEZE_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask