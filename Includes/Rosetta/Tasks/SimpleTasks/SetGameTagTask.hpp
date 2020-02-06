// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SET_GAME_TAG_TASK_HPP
#define ROSETTASTONE_SET_GAME_TAG_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief SetGameTagTask class.
//!
//! This class represents the task for setting game tag to entities.
//!
class SetGameTagTask : public ITask
{
 public:
    //! Constructs task with given \p tag, \p amount and \p entityType.
    //! \param entityType The entity type of target to set game tag.
    //! \param tag A game tag to set.
    //! \param amount A value of game tag to set.
    explicit SetGameTagTask(EntityType entityType, GameTag tag, int amount);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    GameTag m_gameTag = GameTag::INVALID;
    int m_amount = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_SET_GAME_TAG_TASK_HPP
