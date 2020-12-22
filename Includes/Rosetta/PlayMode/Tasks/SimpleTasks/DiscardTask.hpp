// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DISCARD_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DISCARD_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//! The type of discard task.
enum class DiscardType
{
    DEFAULT,       //!< Don't care.
    LOWEST_COST,   //!< Lowest cost card.
    HIGHEST_COST,  //!< Highest cost card.
};

//!
//! \brief DiscardTask class.
//!
//! This class represents the task for discarding card(s) from hand.
//!
class DiscardTask : public ITask
{
 public:
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type of target to discard card(s).
    explicit DiscardTask(EntityType entityType);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DISCARD_TASK_HPP
