// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_TRADE_CARD_TASK_HPP
#define ROSETTASTONE_PLAYMODE_TRADE_CARD_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
//!
//! \brief TradeCardTask class.
//!
//! This class represents the task for trading a card that has an ability
//! "Tradeable".
//!
class TradeCardTask : public ITask
{
 public:
    //! Constructs task with given \p source.
    //! \param source A pointer to card to trade.
    explicit TradeCardTask(Entity* source);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    //! Returns whether a card can trade.
    //! \return Whether a card can trade.
    bool CanTradeCard() const;
};
}  // namespace RosettaStone::PlayMode::PlayerTasks

#endif  // ROSETTASTONE_PLAYMODE_TRADE_CARD_TASK_HPP
