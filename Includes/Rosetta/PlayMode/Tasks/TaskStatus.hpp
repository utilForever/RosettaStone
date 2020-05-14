// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_TASK_STATUS_HPP
#define ROSETTASTONE_PLAYMODE_TASK_STATUS_HPP

namespace RosettaStone::PlayMode
{
using status_t = unsigned int;

//! Meta data to represent the result of the task.
enum class TaskStatus : status_t
{
    INVALID,
    STOP,
    COMPLETE,

    NUM_TASK_STATUS
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TASK_STATUS_HPP
