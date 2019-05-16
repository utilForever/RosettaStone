// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_HERO_POWER_TASK_HPP
#define ROSETTASTONE_HERO_POWER_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief WeaponTask class.
//!
//! This class represents the task for equipping weapon.
//!
class HeroPowerTask : public ITask
{
 public:
    //! Constructs task with given \p cardID.
    //! \param target A pointer to target entity to receive power.
    explicit HeroPowerTask(Entity* target = nullptr);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    std::string m_cardID;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_HERO_POWER_TASK_HPP
