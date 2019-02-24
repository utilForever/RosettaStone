// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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

TaskStatus PoisonousTask::Impl(Player&)
{
    m_target->isDestroyed = true;

    return TaskStatus::POISONOUS_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks