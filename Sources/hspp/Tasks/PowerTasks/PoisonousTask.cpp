// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PowerTasks/PoisonousTask.h>

namespace Hearthstonepp::PowerTask
{
PoisonousTask::PoisonousTask(Character* target) : m_target(target)
{
    // Do nothing
}

TaskID PoisonousTask::GetTaskID() const
{
    return TaskID::POISONOUS;
}

MetaData PoisonousTask::Impl(Player&)
{
    m_target->health = static_cast<size_t>(0);

    return MetaData::POISONOUS_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask