// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TRANSFORM_TASK_HPP
#define ROSETTASTONE_TRANSFORM_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief TransformTask class.
//!
//! This class represents the task for transforming minion to another.
//!
class TransformTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p cardID.
    //! \param entityType The entity type of target to transform.
    //! \param cardID A new card ID to transform.
    explicit TransformTask(EntityType entityType, std::string cardID);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    std::string m_cardID;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_TRANSFORM_TASK_HPP
