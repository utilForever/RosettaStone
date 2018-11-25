// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_H
#define HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
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
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_ADD_ENCHANTMENT_TASK_H
