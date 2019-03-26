// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_POWER_HPP
#define ROSETTASTONE_POWER_HPP

#include <Rosetta/Enchants/Enchant.hpp>

#include <vector>

namespace RosettaStone
{
class ITask;
class Enchant;

//!
//! \brief Power class.
//!
//! This class stores task to perform power and enchant to apply it.
//!
class Power
{
 public:
    //! Returns enchant.
    //! \return A reference to enchant.
    Enchant& GetEnchant();

    //! Returns a list of power tasks.
    //! \return A list of power tasks.
    std::vector<ITask*>& GetPowerTask();

    //! Clears power task and enchant.
    void ClearData();

    //! Adds enchant.
    //! \param enchant An enchant to add.
    void AddEnchant(Enchant&& enchant);

    //! Adds power task to a list of power tasks.
    //! \param task A pointer to power task.
    void AddPowerTask(ITask* task);

 private:
    Enchant m_enchant;

    std::vector<ITask*> m_powerTask;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_POWER_HPP
