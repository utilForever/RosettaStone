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
//! The side of summoned minion.
enum class SummonSide
{
    DEFAULT,      //!< Summoning on the last position on the right side.
    LEFT,         //!< Summoning left of the minion.
    RIGHT,        //!< Summoning right of the minion.
    DEATHRATTLE,  //!< Summoning at the last position of the source.
};

//!
//! \brief SummonTask class.
//!
//! This class represents the task for summoning minion at battlefield.
//!
class SummonTask
{
 public:
    //! Constructs task with given \p cardID, \p amount and \p side.
    //! \param cardID The card ID to summon.
    //! \param amount The number of minions to summon.
    //! \param side The side of summoned minion.
    explicit SummonTask(const std::string_view& cardID, int amount,
                        SummonSide side = SummonSide::DEFAULT);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player);

    Card m_card;
    SummonSide m_side = SummonSide::DEFAULT;
    int m_amount = 1;
};
}  // namespace RosettaStone::Battlegrounds::SimpleTasks

#endif  // ROSETTASTONE_BATTLEGROUNDS_SUMMON_TASK_HPP
