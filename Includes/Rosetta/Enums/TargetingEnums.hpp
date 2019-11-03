// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TARGETING_ENUMS_HPP
#define ROSETTASTONE_TARGETING_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying targeting type.
enum class TargetingType
{
    NONE,
    ALL,
    FRIENDLY_CHARACTERS,
    ENEMY_CHARACTERS,
    ALL_MINIONS,
    FRIENDLY_MINIONS,
    ENEMY_MINIONS,
    HEROES
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TARGETING_ENUMS_HPP
