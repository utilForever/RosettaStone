// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SWAP_ATTACK_HEALTH_TASK_HPP
#define ROSETTASTONE_PLAYMODE_SWAP_ATTACK_HEALTH_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief SwapAttackHealthTask class.
//!
//! This class represents the task for swapping attack and health of entity.
//!
class SwapAttackHealthTask : public ITask
{
 public:
    //! Constructs task with given \p entityType, \p cardID .
    //! \param entityType The entity type of target to swap.
    //! \param enchantmentID The ID of enchantment card.
    explicit SwapAttackHealthTask(EntityType entityType,
                                  std::string enchantmentID);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::string m_enchantmentID;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_SWAP_ATTACK_HEALTH_TASK_HPP
