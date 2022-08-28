// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SUMMON_COPY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_SUMMON_COPY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief SummonCopyTask class.
//!
//! This class represents the task for summoning a copy of one
//! (or more) existing entity.
//!
class SummonCopyTask : public ITask
{
 public:
    //! Constructs task with given various arguments.
    //! \param entityType The entity type to copy.
    //! \param randomFlag true if the copies need to be summoned
    //! in random order, false otherwise.
    //! \param addToStack The flag that adds the summoned entity to the stack.
    //! \param side The side in which the summoned entity should be place.
    explicit SummonCopyTask(EntityType entityType, bool randomFlag = false,
                            bool addToStack = false,
                            SummonSide side = SummonSide::DEFAULT);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    SummonSide m_side = SummonSide::DEFAULT;
    bool m_randomFlag = false;
    bool m_addToStack = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_SUMMON_COPY_TASK_HPP
