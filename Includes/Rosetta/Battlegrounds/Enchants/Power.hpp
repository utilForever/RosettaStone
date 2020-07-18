// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_POWER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_POWER_HPP

#include <Rosetta/Battlegrounds/Enchants/Enchant.hpp>
#include <Rosetta/Battlegrounds/Tasks/TaskType.hpp>
#include <Rosetta/Battlegrounds/Triggers/Trigger.hpp>

#include <optional>
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

    //! Returns a list of start of combat tasks.
    //! \return A list of start of combat tasks.
    std::vector<TaskType>& GetStartCombatTask();

    //! Returns a list of deathrattle tasks.
    //! \return A list of deathrattle tasks.
    std::vector<TaskType>& GetDeathrattleTask();

    //! Returns enchant.
    //! \return A reference to enchant.
    std::optional<Enchant>& GetEnchant();

    //! Returns trigger.
    //! \return A reference to trigger.
    std::optional<Trigger>& GetTrigger();

    //! Adds battlecry task.
    //! \param task A battlecry task to add.
    void AddBattlecryTask(TaskType&& task);

    //! Adds start of combat task.
    //! \param task A start of combat task to add.
    void AddStartCombatTask(TaskType&& task);

    //! Adds deathrattle task.
    //! \param task A deathrattle task to add.
    void AddDeathrattleTask(TaskType&& task);

    //! Adds enchant.
    //! \param enchant An enchant to add.
    void AddEnchant(Enchant&& enchant);

    //! Adds trigger.
    //! \param trigger An trigger to add.
    void AddTrigger(Trigger&& trigger);

 private:
    std::vector<TaskType> m_battlecryTask;
    std::vector<TaskType> m_startCombatTask;
    std::vector<TaskType> m_deathrattleTask;
    std::optional<Enchant> m_enchant;
    std::optional<Trigger> m_trigger;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_POWER_HPP
