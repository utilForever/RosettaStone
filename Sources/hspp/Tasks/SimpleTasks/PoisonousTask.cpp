// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/SimpleTasks/PoisonousTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
PoisonousTask::PoisonousTask(Character* target) : ITask(nullptr, target)
{
    // Do nothing
}

TaskID PoisonousTask::GetTaskID() const
{
    return TaskID::POISONOUS;
}

MetaData PoisonousTask::Impl(Player&)
{
    dynamic_cast<Character*>(m_target)->health = 0;

    return MetaData::POISONOUS_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks