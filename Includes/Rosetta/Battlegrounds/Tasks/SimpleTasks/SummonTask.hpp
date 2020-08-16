// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_SUMMON_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_SUMMON_TASK_HPP

#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <string_view>

namespace RosettaStone::Battlegrounds
{
class Card;
class Minion;
class Player;

namespace SimpleTasks
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
    //! \param addToStack The flag that indicates
    //! whether the summon entity should add to stack.
    explicit SummonTask(const std::string_view& cardID, int amount,
                        SummonSide side = SummonSide::DEFAULT,
                        bool addToStack = false);

    //! Returns the position of minion to summon.
    //! \param source The source minion.
    //! \param side The side of summoned minion.
    //! \return The position of minion to summon.
    static int GetPosition(Minion& source, SummonSide side);

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

    std::string_view m_cardID;
    SummonSide m_side = SummonSide::DEFAULT;
    int m_amount = 1;
    bool m_addToStack = false;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_SUMMON_TASK_HPP
