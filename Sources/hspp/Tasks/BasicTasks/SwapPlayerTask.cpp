// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/InitAttackCountTask.h>
#include <hspp/Tasks/BasicTasks/SwapPlayerTask.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
TaskID SwapPlayerTask::GetTaskID() const
{
    return TaskID::SWAP;
}

MetaData SwapPlayerTask::Impl(Player& player1, Player& player2)
{
    std::swap(player1, player2);
    InitAttackCountTask().Run(player1, player2);

    return MetaData::SWAP_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks