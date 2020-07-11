// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_TASK_STACK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_TASK_STACK_HPP

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
        minions.clear();
        num = 0;
    }

    std::vector<std::reference_wrapper<Minion>> minions;
    int num = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_TASK_STACK_HPP
