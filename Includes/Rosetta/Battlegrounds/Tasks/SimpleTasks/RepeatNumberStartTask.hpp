// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_REPEAT_NUMBER_START_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_REPEAT_NUMBER_START_TASK_HPP

#include <Rosetta/Common/Enums/TaskEnums.hpp>

namespace RosettaStone::Battlegrounds
{
class Card;
class Minion;
class Player;

namespace SimpleTasks
{
//!
//! \brief RepeatNumberStartTask class.
//!
//! This class represents the task for starting to repeat some tasks by a
//! certain number of times.
//!
class RepeatNumberStartTask
{
 public:
    //! Constructs task with given \p num.
    //! \param num The number of times to repeat tasks.
    explicit RepeatNumberStartTask(int num);

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
    int m_num = 0;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_REPEAT_NUMBER_START_TASK_HPP
