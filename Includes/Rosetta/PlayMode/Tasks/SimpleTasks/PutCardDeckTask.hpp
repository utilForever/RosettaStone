// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_PUT_CARD_DECK_TASK_HPP
#define ROSETTASTONE_PLAYMODE_PUT_CARD_DECK_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief PutCardDeckTask class.
//!
//! This class represents the task for putting card(s) on the deck.
//!
class PutCardDeckTask : public ITask
{
 public:
    //! Constructs task with given \p cardID, \p position and \p amount.
    //! \param cardID The ID of card to put on the deck.
    //! \param position The position of card to put on the deck.
    //! \param amount The number of card to put on the deck.
    explicit PutCardDeckTask(std::string cardID, DeckPosition position,
                             int amount = 1);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::string m_cardID;
    DeckPosition m_position;
    int m_amount = 1;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_PUT_CARD_DECK_TASK_HPP
