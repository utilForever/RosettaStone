// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FlagTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
FlagTask::FlagTask(bool flag, std::vector<std::shared_ptr<ITask>> toDoTasks)
    : m_flag(flag), m_toDoTasks(std::move(toDoTasks))
{
    // Do nothing
}

TaskStatus FlagTask::Impl(Player* player)
{
    if (player->game->taskStack.flag != m_flag)
    {
        return TaskStatus::COMPLETE;
    }

    for (const auto& task : m_toDoTasks)
    {
        const std::unique_ptr<ITask> clonedTask = task->Clone();

        clonedTask->SetPlayer(player);
        clonedTask->SetSource(m_source);
        clonedTask->SetTarget(m_target);

        clonedTask->Run();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> FlagTask::CloneImpl()
{
    return std::make_unique<FlagTask>(m_flag, m_toDoTasks);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
