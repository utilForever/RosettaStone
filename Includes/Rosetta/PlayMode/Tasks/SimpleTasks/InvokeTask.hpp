// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_INVOKE_TASK_HPP
#define ROSETTASTONE_PLAYMODE_INVOKE_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief InvokeTask class.
//!
//! This class represents the task for processing ability 'Invoke'. When an
//! Invoke card is played, the Hero Power of Galakrond will be activated, as
//! long as the player has a Galakrond hero card in their hand, deck, or
//! battlefield. Invoke cards are also needed to upgrade Galakrond's Battlecry.
//! Two are needed to upgrade him once, and four are needed to fully upgrade
//! him.
//!
class InvokeTask : public ITask
{
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

#endif  // ROSETTASTONE_PLAYMODE_INVOKE_TASK_HPP
