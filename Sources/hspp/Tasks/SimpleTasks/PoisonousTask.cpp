// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/PoisonousTask.hpp>

namespace Hearthstonepp::SimpleTasks
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
}  // namespace Hearthstonepp::SimpleTasks