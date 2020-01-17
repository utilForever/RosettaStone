// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_HERO_POWER_TASK_HPP
#define ROSETTASTONE_HERO_POWER_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::PlayerTasks
{
//!
//! \brief HeroPowerTask class.
//!
//! This class represents the task for playing hero power.
//!
class HeroPowerTask : public ITask
{
 public:
    //! Constructs task with given \p cardID.
    //! \param target A pointer to target entity to receive power.
    explicit HeroPowerTask(Playable* target = nullptr);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::string m_cardID;
};
}  // namespace RosettaStone::PlayerTasks

#endif  // ROSETTASTONE_HERO_POWER_TASK_HPP
