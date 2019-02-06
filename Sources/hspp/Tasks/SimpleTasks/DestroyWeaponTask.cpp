// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/DestroyWeaponTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
TaskID DestroyWeaponTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

TaskStatus DestroyWeaponTask::Impl(Player& player)
{
    delete player.GetHero()->weapon;
    player.GetHero()->weapon = nullptr;

    return TaskStatus::DESTROY_WEAPON_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks
