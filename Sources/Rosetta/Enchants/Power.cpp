// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Enchants/Power.hpp>

#include <utility>

namespace RosettaStone
{
void Power::RefCopy(const Power& rhs)
{
    m_aura = rhs.m_aura;
    // m_enchant = std::make_unique<Enchant>(*rhs.m_enchant);
    m_trigger = rhs.m_trigger;

    m_powerTask = rhs.m_powerTask;
    m_deathrattleTask = rhs.m_deathrattleTask;
    m_comboTask = rhs.m_comboTask;
}

IAura* Power::GetAura()
{
    return m_aura.get();
}

Enchant* Power::GetEnchant()
{
    return m_enchant.get();
}

Trigger* Power::GetTrigger()
{
    return m_trigger.get();
}

std::vector<std::shared_ptr<ITask>>& Power::GetPowerTask()
{
    return m_powerTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetDeathrattleTask()
{
    return m_deathrattleTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetComboTask()
{
    return m_comboTask;
}

void Power::ClearData()
{
    m_aura.reset();
    m_enchant.reset();
    m_trigger = nullptr;
    m_powerTask.clear();
    m_deathrattleTask.clear();
    m_comboTask.clear();
}

void Power::AddAura(std::shared_ptr<IAura> aura)
{
    m_aura = std::move(aura);
}

void Power::AddEnchant(std::shared_ptr<Enchant> enchant)
{
    m_enchant = std::move(enchant);
}

void Power::AddTrigger(std::shared_ptr<Trigger> trigger)
{
    m_trigger = std::move(trigger);
}

void Power::AddPowerTask(std::shared_ptr<ITask> task)
{
    m_powerTask.emplace_back(task);
}

void Power::AddDeathrattleTask(std::shared_ptr<ITask> task)
{
    m_deathrattleTask.emplace_back(task);
}

void Power::AddComboTask(std::shared_ptr<ITask> task)
{
    m_comboTask.emplace_back(task);
}
}  // namespace RosettaStone
