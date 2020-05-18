// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_TRANSFORM_COPY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_TRANSFORM_COPY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief TransformCopyTask class.
//!
//! This class represents the task for transforming minion to another and coping
//! data such as attack/health, enchantment and so on.
//!
class TransformCopyTask : public ITask
{
 public:
    //! Constructs task with given \p fromTarget.
    //! \param toTarget true if it transforms to target,
    //! false if it transforms from target.
    //! \param addToStack A flag to store transformed card to stack.
    TransformCopyTask(bool toTarget = false, bool addToStack = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    bool m_toTarget = false;
    bool m_addToStack = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_TRANSFORM_COPY_TASK_HPP
