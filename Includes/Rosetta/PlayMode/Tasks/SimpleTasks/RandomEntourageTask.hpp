// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_RANDOM_ENTOURAGE_TASK_HPP
#define ROSETTASTONE_PLAYMODE_RANDOM_ENTOURAGE_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief RandomEntourageTask class.
//!
//! This class represents the task for picking entourage at random.
//!
class RandomEntourageTask : public ITask
{
 public:
    //! Constructs task with given \p count and \p isOpponent.
    //! \param count A value indicating the number of picking.
    //! \param isOpponent A flag to owner indicating opponent player.
    RandomEntourageTask(int count = 1, bool isOpponent = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_count = 1;
    bool m_isOpponent = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_RANDOM_ENTOURAGE_TASK_HPP
