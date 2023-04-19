// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FuncNumberTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
FuncNumberTask::FuncNumberTask(std::function<int(Playable*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

TaskStatus FuncNumberTask::Impl(Player* player)
{
    if (m_func)
    {
        player->game->taskStack.num[0] =
            m_func(dynamic_cast<Playable*>(m_source));
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> FuncNumberTask::CloneImpl()
{
    return std::make_unique<FuncNumberTask>(m_func);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
