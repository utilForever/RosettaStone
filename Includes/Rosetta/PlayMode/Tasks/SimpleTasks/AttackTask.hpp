// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ATTACK_TASK_HPP
#define ROSETTASTONE_PLAYMODE_ATTACK_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief AttackTask class.
//!
//! This class represents the task for attacking the target.
//!
class AttackTask : public ITask
{
 public:
    //! Constructs task with given \p attacker, \p defender and \p force.
    //! \param attacker The entity type of attacker.
    //! \param defender The entity type of defender.
    //! \param force The flag that indicates it is forced attack.
    explicit AttackTask(EntityType attacker, EntityType defender,
                        bool force = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    EntityType m_attackerType = EntityType::INVALID;
    EntityType m_defenderType = EntityType::INVALID;
    bool m_force = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_ATTACK_TASK_HPP
