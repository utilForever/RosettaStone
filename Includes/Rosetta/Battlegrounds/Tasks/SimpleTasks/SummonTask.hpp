// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_SUMMON_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_SUMMON_TASK_HPP

#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>

namespace RosettaStone::Battlegrounds::SimpleTasks
{
//!
//! \brief SummonTask class.
//!
//! This class represents the task for summoning minion at battlefield.
//!
class SummonTask
{
 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player);
};
}  // namespace RosettaStone::Battlegrounds::SimpleTasks

#endif  // ROSETTASTONE_BATTLEGROUNDS_SUMMON_TASK_HPP
