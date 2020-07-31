// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_ADD_ENCHANTMENT_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_ADD_ENCHANTMENT_TASK_HPP

#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <string_view>

namespace RosettaStone::Battlegrounds
{
class Card;
class Minion;
class Player;

namespace SimpleTasks
{
//!
//! \brief AddEnchantmentTask class.
//!
//! This class represents the task for granting enchantment to entity.
//!
class AddEnchantmentTask
{
 public:
    //! Constructs task with given various parameters.
    //! \param cardID The card ID of enchantment to play.
    //! \param entityType The entity type of target to grant.
    //! \param useScriptTag The flag that indicates whether it uses script tag.
    explicit AddEnchantmentTask(const std::string_view& cardID,
                                EntityType entityType,
                                bool useScriptTag = false);

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
    std::string_view m_cardID;
    EntityType m_entityType = EntityType::INVALID;
    bool m_useScriptTag = false;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_ADD_ENCHANTMENT_TASK_HPP
