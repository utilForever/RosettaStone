// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.h>

namespace Hearthstonepp::BasicTasks
{
TaskID DestroyWeaponTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyWeaponTask::Impl(Player& player1, Player&)
{
    delete player1.hero->weapon;
    player1.hero->weapon = nullptr;

    return MetaData::DESTROY_OPPONENT_WEAPON_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
