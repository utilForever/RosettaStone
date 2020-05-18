// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_COPY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_COPY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief CopyTask class.
//!
//! This class represents the task for copying entities.
//!
class CopyTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p amount.
    //! \param entityType The type of entity.
    //! \param zoneType The type of zone.
    //! \param amount The number of entities to copy.
    //! \param addToStack The flag that indicates whether copied entity should
    //! be added to the stack.
    //! \param toOpponent The flag that indicates the owner of copied entity.
    CopyTask(EntityType entityType, ZoneType zoneType, int amount = 1,
             bool addToStack = false, bool toOpponent = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    ZoneType m_zoneType = ZoneType::INVALID;
    int m_amount = 0;
    bool m_addToStack = false;
    bool m_toOpponent = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_COPY_TASK_HPP
