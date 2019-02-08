// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "TestTasks.hpp"

#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Models/Player.hpp>
#include <hspp/Tasks/TaskStatus.hpp>

#include <functional>

using namespace Hearthstonepp;

TestTask::TestTask(TaskID id, std::function<TaskStatus(Player&)>&& impl)
    : m_id(id), m_impl(std::move(impl))
{
    // Do nothing
}

TaskID TestTask::GetTaskID() const
{
    return m_id;
}

TaskStatus TestTask::Impl(Player& player)
{
    return m_impl(player);
}
