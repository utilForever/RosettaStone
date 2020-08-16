// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_SET_GAME_TAG_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_SET_GAME_TAG_TASK_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>

namespace RosettaStone::Battlegrounds
{
class Card;
class Minion;
class Player;

namespace SimpleTasks
{
//!
//! \brief SetGameTagTask class.
//!
//! This class represents the task for setting game tag to minions.
//!
class SetGameTagTask
{
 public:
    //! Constructs task with given \p entityType, \p tag and \p amount.
    //! \param entityType The entity type of target to set game tag.
    //! \param tag A game tag to set.
    //! \param amount A value of game tag to set.
    explicit SetGameTagTask(EntityType entityType, GameTag tag, int amount);

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
    EntityType m_entityType = EntityType::INVALID;
    GameTag m_gameTag = GameTag::INVALID;
    int m_amount = 0;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_SET_GAME_TAG_TASK_HPP
