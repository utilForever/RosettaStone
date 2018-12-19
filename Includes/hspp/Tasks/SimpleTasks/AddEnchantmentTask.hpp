// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_HPP
#define HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::SimpleTasks
{
//!
//! \brief AddEnchantmentTask class.
//!
//! This class represents the task for granting enchantment to entity.
//!
class AddEnchantmentTask : public ITask
{
 public:
    //! Constructs task with given \p cardID and \p entityType.
    //! \param cardID The card ID of enchantment to play.
    //! \param entityType The entity type of target to grant.
    AddEnchantmentTask(std::string&& cardID, EntityType entityType);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    std::string m_cardID;
    EntityType m_entityType = EntityType::EMPTY;
};
}  // namespace Hearthstonepp::SimpleTasks

#endif  // HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_HPP
