// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ADD_ENCHANTMENT_TASK_HPP
#define ROSETTASTONE_PLAYMODE_ADD_ENCHANTMENT_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief AddEnchantmentTask class.
//!
//! This class represents the task for granting enchantment to entity.
//!
class AddEnchantmentTask : public ITask
{
 public:
    //! Constructs task with given various parameters.
    //! \param cardID The card ID of enchantment to play.
    //! \param entityType The entity type of target to grant.
    //! \param useScriptTag The flag that indicates whether it uses script tag.
    //! \param useEntityID The flag that indicates whether it uses entity ID.
    //! \param selfCondition The self condition to check.
    AddEnchantmentTask(
        const std::string_view& cardID, EntityType entityType,
        bool useScriptTag = false, bool useEntityID = false,
        std::optional<SelfCondition> selfCondition = std::nullopt);

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
    bool m_useEntityID = false;
    std::optional<SelfCondition> m_selfCondition = std::nullopt;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_ADD_ENCHANTMENT_TASK_HPP
