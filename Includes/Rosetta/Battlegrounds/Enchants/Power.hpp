// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_POWER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_POWER_HPP

#include <Rosetta/Battlegrounds/Tasks/TaskType.hpp>
#include <Rosetta/Battlegrounds/Triggers/Trigger.hpp>

#include <vector>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Power class.
//!
//! This class stores task to perform power and enchant to apply it.
//!
class Power
{
 public:
    //! Clears a list of tasks and aura/enchant/trigger.
    void ClearData();

    //! Returns a list of battlecry tasks.
    //! \return A list of battlecry tasks.
    std::vector<TaskType>& GetBattlecryTask();

    //! Returns trigger.
    //! \return A reference to trigger.
    Trigger& GetTrigger();

    //! Adds battlecry task.
    //! \param task A battlecry task to add.
    void AddBattlecryTask(TaskType&& task);

    //! Adds trigger.
    //! \param trigger An trigger to add.
    void AddTrigger(Trigger&& trigger);

 private:
    std::vector<TaskType> m_battlecryTask;
    Trigger m_trigger;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_POWER_HPP
