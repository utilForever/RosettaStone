// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SUMMON_STACK_TASK_HPP
#define ROSETTASTONE_PLAYMODE_SUMMON_STACK_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief SummonStackTask class.
//!
//! This class represents the task for summoning something from stack.
//!
class SummonStackTask : public ITask
{
 public:
    //! Constructs task with given \p removeFromZone.
    //! \param removeFromZone true if entity must be removed before it is
    //! summoned from the zone.
    explicit SummonStackTask(bool removeFromZone = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    bool m_removeFromZone = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_SUMMON_STACK_TASK_HPP
