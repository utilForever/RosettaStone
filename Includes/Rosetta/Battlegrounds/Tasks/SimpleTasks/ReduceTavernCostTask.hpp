// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_REDUCE_TAVERN_COST_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_REDUCE_TAVERN_COST_TASK_HPP

#include <Rosetta/Common/Enums/TaskEnums.hpp>

namespace RosettaStone::Battlegrounds
{
class Card;
class Minion;
class Player;

namespace SimpleTasks
{
//!
//! \brief ReduceTavernCostTask class.
//!
//! This class represents the task for reducing the cost of specific button
//! in Tavern.
//!
class ReduceTavernCostTask
{
 public:
    //! Constructs task with given \p button and \p cost.
    //! \param button A specific button in Tavern.
    //! \param cost The value of cost to reduce.
    explicit ReduceTavernCostTask(TavernButton button, int cost);

    //! Runs task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \param source The source minion.
    //! \return The result of task processing.
    TaskStatus Run(Player& player, Minion& source);

    //! Runs task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \param source The source minion.
    //! \param target The target minion.
    //! \return The result of task processing.
    TaskStatus Run(Player& player, Minion& source, Minion& target);

 private:
    TavernButton m_tavernButton;
    int m_cost = 0;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_REDUCE_TAVERN_COST_TASK_HPP
