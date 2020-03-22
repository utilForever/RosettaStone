// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_REMOVE_FROM_HAND_TASK_HPP
#define ROSETTASTONE_REMOVE_FROM_HAND_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief RemoveFromHandTask class.
//!
//! This class represents the task for removing entity from hand.
//!
class RemoveFromHandTask : public ITask
{
 public:
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type to remove from hand.
    explicit RemoveFromHandTask(EntityType entityType);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_REMOVE_FROM_HAND_TASK_HPP
