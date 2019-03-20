// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_DRAW_TASK_HPP
#define HEARTHSTONEPP_DRAW_TASK_HPP

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
    //! Constructs task with given \p agent and \p num.
    //! \param num The number of cards to draw.
    DrawTask(std::size_t num);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    std::size_t m_num = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // HEARTHSTONEPP_DRAW_TASK_HPP
