// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DRAW_RACE_MINION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DRAW_RACE_MINION_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief DrawRaceMinionTask class.
//!
//! This class represents the task for drawing minion card(s)
//! that matches the race from the deck.
//!
class DrawRaceMinionTask : public ITask
{
 public:
    //! Constructs task with given \p race, \p amount and \p addToStack.
    //! \param race The race to draw minion card(s).
    //! \param amount The amount to draw minion card(s).
    //! \param addToStack A flag to store card to stack.
    explicit DrawRaceMinionTask(Race race, int amount, bool addToStack);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    Race m_race = Race::INVALID;
    int m_amount = 0;
    bool m_addToStack = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DRAW_RACE_MINION_TASK_HPP
