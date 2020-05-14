// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DRAW_OP_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DRAW_OP_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief DrawOpTask class.
//!
//! This class represents the task for opponent player drawing card(s) from deck
//! at random.
//!
class DrawOpTask : public ITask
{
 public:
    //! Constructs task with given \p amount and \p toStack.
    //! \param amount The amount to draw card.
    //! \param toStack A flag to store card to stack.
    explicit DrawOpTask(int amount, bool toStack = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_amount = 0;
    bool m_toStack = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DRAW_OP_TASK_HPP