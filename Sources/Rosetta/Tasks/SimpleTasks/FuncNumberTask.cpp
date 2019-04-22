// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <utility>

namespace RosettaStone::SimpleTasks
{
FuncNumberTask::FuncNumberTask(std::function<void(Entity*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

TaskID FuncNumberTask::GetTaskID() const
{
    return TaskID::FUNC_NUMBER;
}

TaskStatus FuncNumberTask::Impl(Player&)
{
    if (m_func != nullptr)
    {
        m_func(m_source);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
