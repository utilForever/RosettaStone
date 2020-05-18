// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_TASK_STACK_HPP
#define ROSETTASTONE_PLAYMODE_TASK_STACK_HPP

namespace RosettaStone::PlayMode
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
        num.fill(0);

        flag = true;
    }

    //! Adds a list of playables.
    //! \param _playables A list of playables to add.
    void AddPlayables(const std::vector<Playable*>& _playables)
    {
        for (auto&& playable : _playables)
        {
            playables.emplace_back(playable);
        }
    }

    std::vector<Playable*> playables;
    std::array<int, 5> num = { 0, 0, 0, 0, 0 };

    bool flag = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TASK_STACK_HPP
