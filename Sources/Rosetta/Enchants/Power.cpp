// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Enchants/Power.hpp>

namespace RosettaStone
{
Enchant& Power::GetEnchant()
{
    return m_enchant;
}

std::vector<ITask*>& Power::GetPowerTask()
{
    return m_powerTask;
}

std::vector<ITask*>& Power::GetDeathrattleTask()
{
    return m_deathrattleTask;
}

void Power::ClearData()
{
    m_powerTask.clear();
    m_deathrattleTask.clear();
}

void Power::AddEnchant(Enchant&& enchant)
{
    m_enchant = std::move(enchant);
}

void Power::AddPowerTask(ITask* task)
{
    m_powerTask.emplace_back(task);
}

void Power::AddDeathrattleTask(ITask* task)
{
    m_deathrattleTask.emplace_back(task);
}
}  // namespace RosettaStone
