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

    Entity* source = nullptr;
    Entity* target = nullptr;

    int num = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;

    bool flag = true;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_STACK_HPP
