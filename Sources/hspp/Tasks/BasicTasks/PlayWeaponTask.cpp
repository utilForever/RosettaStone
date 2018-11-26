// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/PlayWeaponTask.hpp>

namespace Hearthstonepp::BasicTasks
{
PlayWeaponTask::PlayWeaponTask(Entity* entity) : m_entity(entity)
{
    // Do Nothing
}

TaskID PlayWeaponTask::GetTaskID() const
{
    return TaskID::PLAY_WEAPON;
}

MetaData PlayWeaponTask::Impl(Player& player)
{
    player.GetHero()->weapon = dynamic_cast<Weapon*>(m_entity);

    if (player.GetHero()->weapon == nullptr)
    {
        return MetaData::PLAY_WEAPON_DYNAMIC_CAST_FAIL;
    }

    return MetaData::PLAY_WEAPON_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks