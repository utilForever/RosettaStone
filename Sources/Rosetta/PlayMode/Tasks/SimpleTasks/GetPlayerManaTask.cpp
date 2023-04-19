// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetPlayerManaTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus GetPlayerManaTask::Impl(Player* player)
{
    player->game->taskStack.num[0] = player->GetRemainingMana();

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> GetPlayerManaTask::CloneImpl()
{
    return std::make_unique<GetPlayerManaTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
