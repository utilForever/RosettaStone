// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_DRAW_MINION_TASK_HPP
#define ROSETTASTONE_DRAW_MINION_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief DrawMinionTask class.
//!
//! This class represents the task for drawing minion card(s) from the deck.
//!
class DrawMinionTask : public ITask
{
 public:
    //! Constructs task with given \p lowestCost, \p amount and \p addToStack.
    //! \param lowestCost A flag to draw lowest cost card(s).
    //! \param amount The amount to draw minion card(s).
    //! \param addToStack A flag to store card to stack.
    explicit DrawMinionTask(bool lowestCost, int amount, bool addToStack);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_amount = 0;
    bool m_lowestCost = false;
    bool m_addToStack = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_DRAW_MINION_TASK_HPP
