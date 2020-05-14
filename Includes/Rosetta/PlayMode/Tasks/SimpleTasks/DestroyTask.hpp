// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DESTROY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DESTROY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief DestroyTask class.
//!
//! This class represents the task for destroying something such as minion.
//!
class DestroyTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p forceDeathPhase.
    //! \param entityType The entity type of target to destroy.
    //! \param forceDeathPhase The flag that indicates it forces death phase.
    explicit DestroyTask(EntityType entityType, bool forceDeathPhase = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    bool m_forceDeathPhase = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DESTROY_TASK_HPP
