// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TASK_STACK_HPP
#define ROSETTASTONE_TASK_STACK_HPP

namespace RosettaStone
{
//! This struct is temporary data stack for task.
struct TaskStack
{
    std::vector<Entity*> entities;

    bool flag = true;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_STACK_HPP
