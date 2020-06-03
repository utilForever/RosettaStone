// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_MINION_POOL_HPP
#define ROSETTASTONE_BATTLEGROUNDS_MINION_POOL_HPP

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
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
 private:
    std::array<MinionPoolData, NUM_TOTAL_TAVERN_MINIONS> m_minions;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_MINION_POOL_HPP
