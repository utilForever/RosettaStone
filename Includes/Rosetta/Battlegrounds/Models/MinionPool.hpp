// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_MINION_POOL_HPP
#define ROSETTASTONE_BATTLEGROUNDS_MINION_POOL_HPP

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Battlegrounds/Models/Tavern.hpp>
#include <Rosetta/Common/Constants.hpp>

#include <array>

namespace RosettaStone::Battlegrounds
{
using MinionPoolData = std::tuple<Minion, int, bool>;

//!
//! \brief MinionPool class.
//!
//! This class stores a list of minion in pool for Hearthstone: Battlegrounds.
//!
class MinionPool
{
 public:
    //! Initializes the pool to add a list of minions.
    //! \param excludeRace The race to exclude from the pool.
    void Initialize(Race excludeRace);

    //! Returns the count of minions in the pool.
    //! \return The count of minions in the pool.
    std::size_t GetCount() const;

    //! Add minions to player's Tavern according to current tier.
    //! \param player The player context.
    //! \param tavern The tavern to add minions.
    void AddMinionsToTavern(Player& player, Tavern& tavern);

    //! Returns a minion to the pool.
    //! \param idx The pool index of a minion.
    void ReturnMinion(int idx);

    //! Gets a list of minions according various conditions.
    //! \param minTier The minimum number of tier.
    //! \param maxTier The maximum number of tier.
    //! \param isInPoolOnly The flag indicating whether
    //! to return only minions in the pool.
    //! \return A list of minions that matches various conditions.
    std::vector<Minion> GetMinions(int minTier, int maxTier, bool isInPoolOnly);

 private:
    std::array<MinionPoolData, NUM_TOTAL_TAVERN_MINIONS> m_minions;
    std::size_t m_count = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_MINION_POOL_HPP
