// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/TaskSerializer.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp
{
ITask::~ITask()
{
    delete source;
    delete target;
}

MetaData ITask::Run(Player& player1, Player& player2)
{
    return Impl(player1, player2);
}

MetaData ITask::Run(Player& player1, Player& player2, TaskMeta& meta)
{
    MetaData status = Impl(player1, player2);
    meta = Serializer::CreateGameStatus(GetTaskID(), status, player1, player2);

    return status;
}
}  // namespace Hearthstonepp
