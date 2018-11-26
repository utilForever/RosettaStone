// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.hpp>

namespace Hearthstonepp::BasicTasks
{
TaskID DestroyWeaponTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyWeaponTask::Impl(Player& player)
{
    delete player.GetHero()->weapon;
    player.GetHero()->weapon = nullptr;

    return MetaData::DESTROY_WEAPON_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
