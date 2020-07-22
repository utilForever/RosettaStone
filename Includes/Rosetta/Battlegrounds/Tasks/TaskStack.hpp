// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_TASK_STACK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_TASK_STACK_HPP

#include <Rosetta/Battlegrounds/Tasks/TaskType.hpp>

namespace RosettaStone::Battlegrounds
{
class Minion;

//!
//! \brief TaskStack struct.
//!
//! This struct is temporary data stack for task.
//!
struct TaskStack
{
    //! Resets all variables.
    void Reset()
    {
        tasks.clear();
        minions.clear();
        num = 0;
    }

    std::vector<TaskType> tasks;
    std::vector<std::reference_wrapper<Minion>> minions;
    int num = 0;
    bool isStackingTasks = false;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_TASK_STACK_HPP
