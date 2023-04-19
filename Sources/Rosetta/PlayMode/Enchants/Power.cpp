// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Enchants/Power.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
IAura* Power::GetAura() const
{
    return m_aura.get();
}

Enchant* Power::GetEnchant() const
{
    return m_enchant.get();
}

Trigger* Power::GetTrigger() const
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

std::vector<std::shared_ptr<ITask>>& Power::GetAfterChooseForComboTask()
{
    return m_afterChooseForComboTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetOutcastTask()
{
    return m_outcastTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetSpellburstTask()
{
    return m_spellburstTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetFrenzyTask()
{
    return m_frenzyTask;
}

std::vector<std::shared_ptr<ITask>>& Power::GetHonorableKillTask()
{
    return m_honorableKillTask;
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
    m_frenzyTask.clear();
    m_honorableKillTask.clear();
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

void Power::AddPowerTask(const std::shared_ptr<ITask>& task)
{
    m_powerTask.emplace_back(task);
}

void Power::AddPowerTask(TaskList tasks)
{
    m_powerTask.insert(m_powerTask.end(), tasks.begin(), tasks.end());
}

void Power::AddDeathrattleTask(const std::shared_ptr<ITask>& task)
{
    m_deathrattleTask.emplace_back(task);
}

void Power::AddDeathrattleTask(TaskList tasks)
{
    m_deathrattleTask.insert(m_deathrattleTask.end(), tasks.begin(),
                             tasks.end());
}

void Power::AddComboTask(const std::shared_ptr<ITask>& task)
{
    m_comboTask.emplace_back(task);
}

void Power::AddTopdeckTask(const std::shared_ptr<ITask>& task)
{
    m_topdeckTask.emplace_back(task);
}

void Power::AddAfterChooseTask(const std::shared_ptr<ITask>& task)
{
    m_afterChooseTask.emplace_back(task);
}

void Power::AddAfterChooseForComboTask(const std::shared_ptr<ITask>& task)
{
    m_afterChooseForComboTask.emplace_back(task);
}

void Power::AddOutcastTask(const std::shared_ptr<ITask>& task)
{
    m_outcastTask.emplace_back(task);
}

void Power::AddSpellburstTask(const std::shared_ptr<ITask>& task)
{
    m_spellburstTask.emplace_back(task);
}

void Power::AddSpellburstTask(TaskList tasks)
{
    m_spellburstTask.insert(m_spellburstTask.end(), tasks.begin(), tasks.end());
}

void Power::AddFrenzyTask(const std::shared_ptr<ITask>& task)
{
    m_frenzyTask.emplace_back(task);
}

void Power::AddFrenzyTask(TaskList tasks)
{
    m_frenzyTask.insert(m_frenzyTask.end(), tasks.begin(), tasks.end());
}

void Power::AddHonorableKillTask(const std::shared_ptr<ITask>& task)
{
    m_honorableKillTask.emplace_back(task);
}

void Power::AddHonorableKillTask(TaskList tasks)
{
    m_honorableKillTask.insert(m_honorableKillTask.end(), tasks.begin(),
                               tasks.end());
}
}  // namespace RosettaStone::PlayMode
