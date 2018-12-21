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

MetaData PoisonousTask::Impl(Player&)
{
    dynamic_cast<Character*>(m_target)->health = 0;

    return MetaData::POISONOUS_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks