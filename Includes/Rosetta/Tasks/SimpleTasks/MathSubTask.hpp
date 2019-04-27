// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_MATH_SUB_TASK_HPP
#define ROSETTASTONE_MATH_SUB_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief MathSubTask class.
//!
//! This class represents the task for subtracting amount of game tag.
//!
class MathSubTask : public ITask
{
 public:
    //! Constructs task with given \p entityType, \p tag and \p amount.
    //! \param entityType The entity type of target to set game tag.
    //! \param tag A game tag to subtract.
    //! \param amount A value to subtract.
    MathSubTask(EntityType entityType, GameTag tag, int amount);

    //! Constructs task with given \p entityType and \p tag.
    //! \param entityType The entity type of target to set game tag.
    //! \param tag A game tag to subtract amount.
    MathSubTask(EntityType entityType, GameTag tag);

    //! Constructs task with given \p amount.
    //! \param amount A value to subtract.
    MathSubTask(int amount);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    GameTag m_gameTag = GameTag::INVALID;
    int m_amount = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_MATH_SUB_TASK_HPP
