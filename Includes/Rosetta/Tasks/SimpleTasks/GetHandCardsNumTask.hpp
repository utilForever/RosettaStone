// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_GET_HAND_CARDS_NUM_HPP
#define ROSETTASTONE_GET_HAND_CARDS_NUM_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief GetHandCardsNumTask class.
//!
//! This class represents the task for getting player or opponent hand cards num.
//!
class GetHandCardsNumTask : public ITask
{
 public:
    //! Constructs task with given \p entityType \p numIndex
    //! \param entityType The entity type of hand that want to find (HAND or ENEMY_HAND).
    //! \param numIndex An index of number.
    GetHandCardsNumTask(EntityType entityType, int numIndex = 0);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    int m_numIndex = 0;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_GET_HAND_CARDS_NUM_HPP
