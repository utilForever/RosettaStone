// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_POWER_HPP
#define HEARTHSTONEPP_POWER_HPP

#include <hspp/Enchants/Enchant.hpp>

#include <vector>

namespace Hearthstonepp
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
    //! Returns a list of power tasks.
    //! \return A list of power tasks.
    std::vector<ITask*>& GetPowerTask();

    //! Returns enchant.
    //! \return A pointer to enchant.
    Enchant* GetEnchant() const;

    //! Clears power task and enchant.
    void ClearData();

    //! Adds power task to a list of power tasks.
    //! \param task A pointer to power task.
    void AddPowerTask(ITask* task);

    //! Adds enchant.
    //! \param enchant A pointer to enchant.
    void AddEnchant(Enchant* enchant);

 private:
    std::vector<ITask*> m_powerTask;
    Enchant* m_enchant = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_POWER_HPP