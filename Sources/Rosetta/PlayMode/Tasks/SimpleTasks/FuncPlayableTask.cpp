// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FuncPlayableTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
FuncPlayableTask::FuncPlayableTask(
    std::function<std::vector<Playable*>(std::vector<Playable*>)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

TaskStatus FuncPlayableTask::Impl(Player* player)
{
    if (m_func)
    {
        player->game->taskStack.playables =
            m_func(player->game->taskStack.playables);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> FuncPlayableTask::CloneImpl()
{
    return std::make_unique<FuncPlayableTask>(m_func);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
