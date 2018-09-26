#include <Tasks/BasicTasks/DestroyWeaponTask.h>

namespace Hearthstonepp::BasicTasks
{
TaskID DestroyWeaponTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyWeaponTask::Impl(Player& player1, Player&)
{
    player1.hero->weapon = nullptr;
    return MetaData::DESTROY_OPPONENT_WEAPON_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
