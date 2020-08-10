// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_POWER_HPP
#define ROSETTASTONE_PLAYMODE_POWER_HPP

#include <Rosetta/PlayMode/Auras/Aura.hpp>
#include <Rosetta/PlayMode/Enchants/Enchant.hpp>
#include <Rosetta/PlayMode/Triggers/Trigger.hpp>

#include <memory>
#include <vector>

namespace RosettaStone::PlayMode
{
class ITask;
class Aura;
class Enchant;

//!
//! \brief Power class.
//!
//! This class stores task to perform power and enchant to apply it.
//!
class Power
{
 public:
    //! Returns aura.
    IAura* GetAura();

    //! Returns enchant.
    //! \return A reference to enchant.
    Enchant* GetEnchant();

    //! Returns trigger.
    //! \return A reference to trigger.
    Trigger* GetTrigger();

    //! Returns a list of power tasks.
    //! \return A list of power tasks.
    std::vector<std::shared_ptr<ITask>>& GetPowerTask();

    //! Returns a list of deathrattle tasks.
    //! \return A list of deathrattle tasks.
    std::vector<std::shared_ptr<ITask>>& GetDeathrattleTask();

    //! Returns a list of combo tasks.
    //! \return A list of combo tasks.
    std::vector<std::shared_ptr<ITask>>& GetComboTask();

    //! Returns a list of topdeck tasks.
    //! \return A list of topdeck tasks.
    std::vector<std::shared_ptr<ITask>>& GetTopdeckTask();

    //! Returns a list of after choose tasks.
    //! \return A list of after choose tasks.
    std::vector<std::shared_ptr<ITask>>& GetAfterChooseTask();

    //! Returns a list of outcast tasks.
    //! \return A list of outcast tasks.
    std::vector<std::shared_ptr<ITask>>& GetOutcastTask();

    //! Returns a list of spellburst tasks.
    //! \return A list of spellburst tasks.
    std::vector<std::shared_ptr<ITask>>& GetSpellburstTask();

    //! Clears power task and enchant.
    void ClearData();

    //! Adds aura.
    //! \param aura An aura to add.
    void AddAura(std::shared_ptr<IAura> aura);

    //! Adds enchant.
    //! \param enchant An enchant to add.
    void AddEnchant(std::shared_ptr<Enchant> enchant);

    //! Adds trigger.
    //! \param trigger An trigger to add.
    void AddTrigger(std::shared_ptr<Trigger> trigger);

    //! Adds power task.
    //! \param task A pointer to power task.
    void AddPowerTask(std::shared_ptr<ITask> task);

    //! Adds deathrattle task.
    //! \param task A pointer to deathrattle task.
    void AddDeathrattleTask(std::shared_ptr<ITask> task);

    //! Adds combo task.
    //! \param task A pointer to combo task.
    void AddComboTask(std::shared_ptr<ITask> task);

    //! Adds topdeck task.
    //! \param task A pointer to topdeck task.
    void AddTopdeckTask(std::shared_ptr<ITask> task);

    //! Adds after choose task.
    //! \param task A pointer to after choose task.
    void AddAfterChooseTask(std::shared_ptr<ITask> task);

    //! Adds outcast task.
    //! \param task A pointer to outcast task.
    void AddOutcastTask(std::shared_ptr<ITask> task);

    //! Adds spellburst task.
    //! \param task A pointer to spellburst task.
    void AddSpellburstTask(std::shared_ptr<ITask> task);

 private:
    std::shared_ptr<IAura> m_aura;
    std::shared_ptr<Enchant> m_enchant;
    std::shared_ptr<Trigger> m_trigger;

    std::vector<std::shared_ptr<ITask>> m_powerTask;
    std::vector<std::shared_ptr<ITask>> m_deathrattleTask;
    std::vector<std::shared_ptr<ITask>> m_comboTask;
    std::vector<std::shared_ptr<ITask>> m_topdeckTask;
    std::vector<std::shared_ptr<ITask>> m_afterChooseTask;
    std::vector<std::shared_ptr<ITask>> m_outcastTask;
    std::vector<std::shared_ptr<ITask>> m_spellburstTask;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_POWER_HPP
