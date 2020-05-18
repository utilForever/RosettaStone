// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_MATH_RAND_TASK_HPP
#define ROSETTASTONE_PLAYMODE_MATH_RAND_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief MathRandTask class.
//!
//! This class represents the task for getting the number at random.
//!
class MathRandTask : public ITask
{
 public:
    //! Constructs task with given \p min and \p max.
    //! \param min The minimum value.
    //! \param max The maximum value.
    explicit MathRandTask(int min, int max);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_min = 0;
    int m_max = 0;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_MATH_RAND_TASK_HPP
