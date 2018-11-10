// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "TestTasks.h"

#include <hspp/Accounts/Player.h>
#include <hspp/Enums/TaskEnums.h>
#include <hspp/Tasks/MetaData.h>

#include <functional>

using namespace Hearthstonepp;

TestTask::TestTask(TaskID id, std::function<MetaData(Player&, Player&)>&& impl)
    : m_id(id), m_impl(std::move(impl))
{
    // Do nothing
}

TaskID TestTask::GetTaskID() const
{
    return m_id;
}

MetaData TestTask::Impl(Player& player1, Player& player2)
{
    return m_impl(player1, player2);
}
