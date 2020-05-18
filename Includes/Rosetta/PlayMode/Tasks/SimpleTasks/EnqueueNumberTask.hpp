// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ENQUEUE_NUMBER_TASK_HPP
#define ROSETTASTONE_PLAYMODE_ENQUEUE_NUMBER_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief EnqueueNumberTask class.
//!
//! This class represents the task for repeating some tasks by
//! a certain number of times.
//!
class EnqueueNumberTask : public ITask
{
 public:
    //! Constructs task with given \p tasks and \p isSpellDamage.
    //! \param tasks A task vector to repeat.
    //! \param isSpellDamage true if it is spell damage, and false otherwise.
    explicit EnqueueNumberTask(std::vector<std::shared_ptr<ITask>> tasks,
                               bool isSpellDamage = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::vector<std::shared_ptr<ITask>> m_tasks;
    bool m_isSpellDamage = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_ENQUEUE_NUMBER_TASK_HPP
