// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_GET_GAME_TAG_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GET_GAME_TAG_TASK_HPP

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
//! \brief GetGameTagTask class.
//!
//! This class represents the task for getting game tag from minions.
//!
class GetGameTagTask
{
 public:
    //! Constructs task with given \p entityType, \p tag, and \p minionIdx.
    //! \param entityType The entity type of target to get game tag.
    //! \param minionIndex An index of minion in the field.
    //! \param tag A game tag to get.
    explicit GetGameTagTask(EntityType entityType, GameTag tag,
                            int minionIndex = 0);

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
    int m_minionIndex = 0;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GET_GAME_TAG_TASK_HPP
