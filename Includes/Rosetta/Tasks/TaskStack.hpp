// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TASK_STACK_HPP
#define ROSETTASTONE_TASK_STACK_HPP

namespace RosettaStone
{
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
        playables.clear();

        source = nullptr;
        target = nullptr;

        num = 0;
        num1 = 0;

        flag = true;
    }

    std::vector<Playable*> playables;

    Entity* source = nullptr;
    Playable* target = nullptr;

    int num = 0;
    int num1 = 0;

    bool flag = true;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_STACK_HPP
