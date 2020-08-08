// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Enchants/Power.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
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

std::vector<std::shared_ptr<ITask>>& Power::GetTopdeckTask()
{
    return m_topdeckTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetAfterChooseTask()
{
    return m_afterChooseTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetOutcastTask()
{
    return m_outcastTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetSpellburstTask()
{
    return m_spellburstTask;
}

void Power::ClearData()
{
    m_aura.reset();
    m_enchant.reset();
    m_trigger = nullptr;

    m_powerTask.clear();
    m_deathrattleTask.clear();
    m_comboTask.clear();
    m_topdeckTask.clear();
    m_afterChooseTask.clear();
    m_outcastTask.clear();
    m_spellburstTask.clear();
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

void Power::AddTopdeckTask(std::shared_ptr<ITask> task)
{
    m_topdeckTask.emplace_back(task);
}

void Power::AddAfterChooseTask(std::shared_ptr<ITask> task)
{
    m_afterChooseTask.emplace_back(task);
}

void Power::AddOutcastTask(std::shared_ptr<ITask> task)
{
    m_outcastTask.emplace_back(task);
}

void Power::AddSpellburstTask(std::shared_ptr<ITask> task)
{
    m_spellburstTask.emplace_back(task);
}
}  // namespace RosettaStone::PlayMode
