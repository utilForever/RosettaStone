// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ADD_ENCHANTMENT_TASK_HPP
#define ROSETTASTONE_ADD_ENCHANTMENT_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief AddEnchantmentTask class.
//!
//! This class represents the task for granting enchantment to entity.
//!
class AddEnchantmentTask : public ITask
{
 public:
    //! Constructs task with given \p cardID, \p entityType and \p useScriptTag.
    //! \param cardID The card ID of enchantment to play.
    //! \param entityType The entity type of target to grant.
    //! \param useScriptTag The flag that indicates whether it uses script tag.
    AddEnchantmentTask(const std::string& cardID, EntityType entityType,
                       bool useScriptTag = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    Card* m_enchantmentCard = nullptr;
    bool m_useScriptTag = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_ADD_ENCHANTMENT_TASK_HPP
