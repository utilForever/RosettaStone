// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/CustomTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
CustomTask::CustomTask(std::function<void(Player*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

TaskStatus CustomTask::Impl(Player* player)
{
    m_func(player);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> CustomTask::CloneImpl()
{
    return std::make_unique<CustomTask>(m_func);
}
}  // namespace RosettaStone::SimpleTasks
