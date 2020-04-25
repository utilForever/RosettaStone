// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_COUNT_TASK_HPP
#define ROSETTASTONE_COUNT_TASK_HPP

#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief CountTask class.
//!
//! This class represents the task for counting entities.
//!
class CountTask : public ITask
{
 public:
    //! Constructs task with given \p entityType, \p numIndex and \p conditions.
    //! \param entityType The type of entity.
    //! \param numIndex An index of number.
    //! \param conditions SelfConditions to check.
    CountTask(EntityType entityType, int numIndex = 0,
              std::vector<SelfCondition> conditions = {});

    //! Constructs task with given \p zoneType, \p getFreeSpace and \p opponent.
    //! \param zoneType The type of zone.
    //! \param getFreeSpace The flag to count the free space of zone.
    //! \param opponent The flag to count for the opponent player.
    CountTask(ZoneType zoneType, bool getFreeSpace, bool opponent);

    //! Constructs task with given various arguments.
    //! \param entityType The type of entity.
    //! \param numIndex An index of number.
    //! \param conditions SelfConditions to check.
    //! \param zoneType The type of zone.
    //! \param getFreeSpace The flag to count the free space of zone.
    //! \param opponent The flag to count for the opponent player.
    CountTask(EntityType entityType, int numIndex,
              std::vector<SelfCondition> conditions, ZoneType zoneType,
              bool getFreeSpace, bool opponent);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    ZoneType m_zoneType = ZoneType::INVALID;
    std::vector<SelfCondition> m_conditions = {};
    int m_numIndex = 0;
    bool m_getFreeSpace = false;
    bool m_opponent = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_COUNT_TASK_HPP
