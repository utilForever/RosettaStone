#include <Tasks/BasicTasks/BriefTask.h>

namespace Hearthstonepp::BasicTasks
{
TaskID BriefTask::GetTaskID() const
{
    return TaskID::BRIEF;
}

MetaData BriefTask::Impl(Player&, Player&)
{
    return MetaData::BRIEF;
}
}  // namespace Hearthstonepp::BasicTasks