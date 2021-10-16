// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DESTROY_DECK_CARD_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DESTROY_DECK_CARD_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief DestroyDeckCardTask class.
//!
//! This class represents the task for destroying card(s) in the deck.
//!
class DestroyDeckCardTask : public ITask
{
 public:
    //! Constructs task with given \p amount and \p isOpponent.
    //! \param amount The number of card(s) to destroy in the deck.
    //! \param isOpponent A flag to owner indicating opponent player.
    DestroyDeckCardTask(int amount, bool isOpponent);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_amount = 0;
    bool m_isOpponent = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DESTROY_DECK_CARD_TASK_HPP
