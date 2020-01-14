// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_POWER_HPP
#define ROSETTASTONE_POWER_HPP

#include <Rosetta/Auras/Aura.hpp>
#include <Rosetta/Enchants/Enchant.hpp>
#include <Rosetta/Enchants/Trigger.hpp>

#include <memory>
#include <vector>

namespace RosettaStone
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
    std::vector<ITask*>& GetPowerTask();

    //! Returns a list of deathrattle tasks.
    //! \return A list of deathrattle tasks.
    std::vector<ITask*>& GetDeathrattleTask();

    //! Returns a list of combo tasks.
    //! \return A list of combo tasks.
    std::vector<ITask*>& GetComboTask();

    //! Clears power task and enchant.
    void ClearData();

    //! Adds aura.
    //! \param aura An aura to add.
    void AddAura(IAura* aura);

    //! Adds enchant.
    //! \param enchant An enchant to add.
    void AddEnchant(std::unique_ptr<Enchant> enchant);

    //! Adds trigger.
    //! \param trigger An trigger to add.
    void AddTrigger(Trigger* trigger);

    //! Adds power task.
    //! \param task A pointer to power task.
    void AddPowerTask(ITask* task);

    //! Adds deathrattle task.
    //! \param task A pointer to deathrattle task.
    void AddDeathrattleTask(ITask* task);

    //! Adds combo task.
    //! \param task A pointer to combo task.
    void AddComboTask(ITask* task);

 private:
    IAura* m_aura = nullptr;
    std::unique_ptr<Enchant> m_enchant;
    Trigger* m_trigger = nullptr;

    std::vector<ITask*> m_powerTask;
    std::vector<ITask*> m_deathrattleTask;
    std::vector<ITask*> m_comboTask;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_POWER_HPP
