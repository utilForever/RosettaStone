// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CHANGE_HERO_POWER_TASK_HPP
#define ROSETTASTONE_PLAYMODE_CHANGE_HERO_POWER_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief ChangeHeroPowerTask class.
//!
//! This class represents the task for changing hero power.
//!
class ChangeHeroPowerTask : public ITask
{
 public:
    //! Constructs task with given \p cardID
    //! \param cardID The card ID to be hero power.
    explicit ChangeHeroPowerTask(const std::string& cardID);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    Card* m_card = nullptr;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_CHANGE_HERO_POWER_TASK_HPP
