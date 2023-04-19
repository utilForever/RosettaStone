// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/WeaponStackTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
WeaponStackTask::WeaponStackTask(bool removeFromZone)
    : m_removeFromZone(removeFromZone)
{
    // Do nothing
}

TaskStatus WeaponStackTask::Impl(Player* player)
{
    const auto stack = player->game->taskStack;

    for (auto& playable : stack.playables)
    {
        if (m_removeFromZone)
        {
            playable->zone->Remove(playable);
        }

        Generic::PlayWeapon(player, dynamic_cast<Weapon*>(playable), nullptr);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> WeaponStackTask::CloneImpl()
{
    return std::make_unique<WeaponStackTask>(m_removeFromZone);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
