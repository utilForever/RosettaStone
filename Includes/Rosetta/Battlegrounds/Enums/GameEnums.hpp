// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_GAME_ENUMS_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GAME_ENUMS_HPP

namespace RosettaStone::Battlegrounds
{
//! \brief An enumerator for identifying the phase.
enum class Phase
{
    INVALID,
    SELECT_HERO,
    RECRUIT,
    COMBAT
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_GAME_ENUMS_HPP
