// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_COPY_TASK_HPP
#define ROSETTASTONE_COPY_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
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
    //! \param amount The number of entities to copy.
    //! \param isOpposite Whether an owner of entity is opposite player.
    //! \param zoneType The type of zone.
    CopyTask(EntityType entityType, int amount, bool isOpposite = false,
             ZoneType zoneType = ZoneType::INVALID);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

    //! Returns Clone Of Object (pure virtual).
    //! \returns clone of object.
    //! \this uses for thread safe. not to access same task in multiple threads
    ITask* CloneImpl() override;;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    int m_amount = 0;
    bool m_isOpposite = false;
    ZoneType m_zoneType = ZoneType::INVALID;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_COPY_TASK_HPP
