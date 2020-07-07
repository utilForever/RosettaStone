// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Power.hpp>

namespace RosettaStone::Battlegrounds
{
void Power::ClearData()
{
    m_battlecryTask.clear();
}

std::vector<TaskType>& Power::GetBattlecryTask()
{
    return m_battlecryTask;
}

std::optional<Trigger>& Power::GetTrigger()
{
    return m_trigger;
}

void Power::AddBattlecryTask(TaskType&& task)
{
    m_battlecryTask.emplace_back(task);
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
