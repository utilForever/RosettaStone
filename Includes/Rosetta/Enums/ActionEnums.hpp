// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_ACTION_ENUMS_HPP
#define ROSETTASTONE_ACTION_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying main operation type.
enum class MainOpType
{
    PLAY_CARD,
    ATTACK,
    USE_HERO_POWER,
    END_TURN
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_ENUMS_HPP
