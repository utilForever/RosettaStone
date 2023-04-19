// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ClearStackTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus ClearStackTask::Impl(Player* player)
{
    player->game->taskStack.playables.clear();

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ClearStackTask::CloneImpl()
{
    return std::make_unique<ClearStackTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
