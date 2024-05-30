// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Power.hpp>

namespace RosettaStone::Battlegrounds
{
void Power::ClearData()
{
    m_battlecryTask.clear();
    m_startCombatTask.clear();
    m_deathrattleTask.clear();
    m_enchant.reset();
    m_trigger.reset();
}

std::vector<TaskType>& Power::GetBattlecryTask()
{
    return m_battlecryTask;
}

std::vector<TaskType>& Power::GetStartCombatTask()
{
    return m_startCombatTask;
}

std::vector<TaskType>& Power::GetDeathrattleTask()
{
    return m_deathrattleTask;
}

std::optional<Enchant>& Power::GetEnchant()
{
    return m_enchant;
}

std::optional<Trigger>& Power::GetTrigger()
{
    return m_trigger;
}

void Power::AddBattlecryTask(TaskType&& task)
{
    m_battlecryTask.emplace_back(task);
}

void Power::AddStartCombatTask(TaskType&& task)
{
    m_startCombatTask.emplace_back(task);
}

void Power::AddDeathrattleTask(TaskType&& task)
{
    m_deathrattleTask.emplace_back(task);
}

void Power::AddEnchant(Enchant&& enchant)
{
    m_enchant = enchant;
}

void Power::AddTrigger(Trigger&& trigger)
{
    m_trigger = trigger;
}
}  // namespace RosettaStone::Battlegrounds
