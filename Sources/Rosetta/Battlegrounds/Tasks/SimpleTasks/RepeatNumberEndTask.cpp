// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/RepeatNumberEndTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
TaskStatus RepeatNumberEndTask::Run(Player& player, Minion& source)
{
    for (int i = 0; i < player.taskStack.num; ++i)
    {
        for (auto& task : player.taskStack.tasks)
        {
            std::visit([&](auto&& _task) { _task.Run(player, source); }, task);
        }
    }

    player.taskStack.isStackingTasks = false;

    return TaskStatus::COMPLETE;
}

TaskStatus RepeatNumberEndTask::Run(Player& player, Minion& source,
                                    Minion& target)
{
    for (int i = 0; i < player.taskStack.num; ++i)
    {
        for (auto& task : player.taskStack.tasks)
        {
            std::visit([&](auto&& _task) { _task.Run(player, source, target); },
                       task);
        }
    }

    player.taskStack.isStackingTasks = false;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
