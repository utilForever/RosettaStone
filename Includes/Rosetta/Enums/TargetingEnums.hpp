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
    CHARACTERS_EXCEPT_HERO,
    FRIENDLY_CHARACTERS,
    ENEMY_CHARACTERS,
    ALL_MINIONS,
    FRIENDLY_MINIONS,
    ENEMY_MINIONS,
    HEROES
};

//! \brief An enumerator for identifying character type.
enum class CharacterType
{
    CHARACTERS,
    CHARACTERS_EXCEPT_HERO,
    HEROES,
    MINIONS
};

//! \brief An enumerator for identifying friendly type.
enum class FriendlyType
{
    ALL,
    FRIENDLY,
    ENEMY
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TARGETING_ENUMS_HPP
