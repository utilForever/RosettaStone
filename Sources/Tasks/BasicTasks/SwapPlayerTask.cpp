#include <Tasks/BasicTasks/InitAttackCountTask.h>
#include <Tasks/BasicTasks/SwapPlayerTask.h>

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