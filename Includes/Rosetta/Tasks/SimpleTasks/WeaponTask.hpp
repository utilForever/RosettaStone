// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_WEAPON_TASK_HPP
#define ROSETTASTONE_WEAPON_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief WeaponTask class.
//!
//! This class represents the task for equipping weapon.
//!
class WeaponTask : public ITask
{
 public:
    //! Constructs task with given \p cardID.
    //! \param cardID The card ID of weapon to equip.
    explicit WeaponTask(std::string cardID);

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
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_WEAPON_TASK_HPP
