// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ATTACK_TASK_HPP
#define ROSETTASTONE_ATTACK_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::PlayerTasks
{
//!
//! \brief AttackTask class.
//!
//! This class represents the task for attacking target.
//!
class AttackTask : public ITask
{
 public:
    //! Construct task with given \p source and \p target.
    //! \param source A pointer to source character.
    //! \param target A pointer to target character.
    AttackTask(Entity* source, Playable* target);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;
};
}  // namespace RosettaStone::PlayerTasks

#endif  // ROSETTASTONE_ATTACK_TASK_HPP
