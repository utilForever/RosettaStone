// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CHANGE_ATTACKING_TARGET_TASK_HPP
#define ROSETTASTONE_PLAYMODE_CHANGE_ATTACKING_TARGET_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief ChangeAttackingTargetTask class.
//!
//! This class represents the task for changing the target of attacking.
//!
class ChangeAttackingTargetTask : public ITask
{
 public:
    //! Constructs task with given \p typeA and \p typeB.
    //! \param typeA The attacker.
    //! \param typeB The new defender.
    explicit ChangeAttackingTargetTask(EntityType typeA, EntityType typeB);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    EntityType m_typeA;
    EntityType m_typeB;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_CHANGE_ATTACKING_TARGET_TASK_HPP
