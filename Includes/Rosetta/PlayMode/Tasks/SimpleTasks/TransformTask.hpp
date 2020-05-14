// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_TRANSFORM_TASK_HPP
#define ROSETTASTONE_PLAYMODE_TRANSFORM_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
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

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::string m_cardID;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_TRANSFORM_TASK_HPP
