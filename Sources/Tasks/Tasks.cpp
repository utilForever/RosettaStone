#include <Tasks/TaskSerializer.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp
{
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
