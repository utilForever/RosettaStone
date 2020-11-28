// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_TRANSFORM_MINION_TASK_HPP
#define ROSETTASTONE_PLAYMODE_TRANSFORM_MINION_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief TransformMinionTask class.
//!
//! This class represents the task for transforming minion to another at random.
//!
class TransformMinionTask : public ITask
{
 public:
    //! Constructs task with given \p entityType, \p race and \p costChange.
    //! \param entityType The entity type to transform.
    //! \param race The value of race to change for transform.
    //! \param costChange The value of cost to change for transform.
    TransformMinionTask(EntityType entityType, Race race, int costChange);

    //! Constructs task with given \p entityType and \p race.
    //! \param entityType The entity type to transform.
    //! \param race The value of race to change for transform.
    TransformMinionTask(EntityType entityType, Race race);

    //! Constructs task with given \p entityType and \p costChange.
    //! \param entityType The entity type to transform.
    //! \param costChange The value of cost to change for transform.
    TransformMinionTask(EntityType entityType, int costChange);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    Race m_race = Race::INVALID;
    int m_costChange = 0;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_TRANSFORM_MINION_TASK_HPP
