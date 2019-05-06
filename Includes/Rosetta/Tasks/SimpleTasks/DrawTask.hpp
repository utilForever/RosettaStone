// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_DRAW_TASK_HPP
#define ROSETTASTONE_DRAW_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief DrawTask class.
//!
//! This class represents the task for drawing card(s) from deck at random.
//!
class DrawTask : public ITask
{
 public:
    //! Constructs task with given \p amount.
    //! \param amount The amount to draw card.
    explicit DrawTask(int amount);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    int m_amount = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_DRAW_TASK_HPP
