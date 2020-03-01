// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_GET_GAME_TAG_TASK_HPP
#define ROSETTASTONE_GET_GAME_TAG_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief GetGameTagTask class.
//!
//! This class represents the task for getting game tag from entities.
//!
class GetGameTagTask : public ITask
{
 public:
    //! Constructs task with given \p entityType, \p tag, \p entityIndex and
    //! \p numIndex.
    //! \param entityType The entity type of target to get game tag.
    //! \param tag A game tag to get.
    //! \param entityIndex An index of entity.
    //! \param numIndex An index of number.
    GetGameTagTask(EntityType entityType, GameTag tag, int entityIndex = 0,
                   int numIndex = 0);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    GameTag m_gameTag = GameTag::INVALID;
    int m_entityIndex = 0;
    int m_numIndex = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_GET_GAME_TAG_TASK_HPP
