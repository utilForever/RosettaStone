// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/RepeatNumberStartTask.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
RepeatNumberStartTask::RepeatNumberStartTask(int num) : m_num(num)
{
    // Do nothing
}

TaskStatus RepeatNumberStartTask::Run(Player& player,
                                      [[maybe_unused]] Minion& source)
{
    player.taskStack.num = m_num;
    player.taskStack.isStackingTasks = true;

    return TaskStatus::COMPLETE;
}

TaskStatus RepeatNumberStartTask::Run(Player& player,
                                      [[maybe_unused]] Minion& source,
                                      [[maybe_unused]] Minion& target)
{
    player.taskStack.num = m_num;
    player.taskStack.isStackingTasks = true;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::Battlegrounds::SimpleTasks
