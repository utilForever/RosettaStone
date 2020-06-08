// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_GAME_UTILS_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GAME_UTILS_HPP

#include <cstddef>

namespace RosettaStone::Battlegrounds
{
//! Returns the number of minions that can purchase in Tavern.
//! \param tier The current tier of the player.
//! \return The number of minions that can purchase in Tavern.
std::size_t GetNumMinionsCanPurchase(int tier);
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GAME_UTILS_HPP
