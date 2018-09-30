#include <hspp/Tasks/BasicTasks/GameEndTask.h>

namespace Hearthstonepp::BasicTasks
{
TaskID GameEndTask::GetTaskID() const
{
    return TaskID::GAME_END;
}

MetaData GameEndTask::Impl(Player&, Player&)
{
    return MetaData::GAME_END;
}
}  // namespace Hearthstonepp::BasicTasks