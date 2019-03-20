// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TASK_ENUMS_HPP
#define HEARTHSTONEPP_TASK_ENUMS_HPP

#ifdef _MSC_VER
#define HEARTHSTONEPP_EXPAND_LARGE_ENUMS
#else  // _MSC_VER
#undef BETTER_ENUMS_MACRO_FILE
#define BETTER_ENUMS_MACRO_FILE "hspp/Commons/EnumMacros.hpp"
#endif  // _MSC_VER

#include <better-enums/enum.h>

namespace Hearthstonepp
{
//! \brief An enumerator for identifying each task.
#ifndef HEARTHSTONEPP_DOXYGEN
BETTER_ENUM(TaskID, int, INVALID, DRAW, OVERDRAW, MODIFY_MANA, DAMAGE, MULLIGAN,
            PLAY_CARD, ADD_ENCHANTMENT, DESTROY, DISCARD, HEAL_FULL, POISONOUS,
            FREEZE, HEAL, INCLUDE, CONTROL, END_TURN, CHOOSE, ATTACK);
#else
enum class TaskID
{
    INVALID,
    DRAW,
    OVERDRAW,
    MODIFY_MANA,
    DAMAGE,
    MULLIGAN,
    PLAY_CARD,
    ADD_ENCHANTMENT,
    DESTROY,
    DISCARD,
    HEAL_FULL,
    POISONOUS,
    FREEZE,
    HEAL,
    INCLUDE,
    CONTROL,
    END_TURN,
    CHOOSE,
    ATTACK
};
#endif

//! \brief An enumerator for identifying entity type.
#ifndef HEARTHSTONEPP_DOXYGEN
BETTER_ENUM(EntityType, int, EMPTY, SOURCE, TARGET, FRIENDS, ENEMIES, HERO,
            ENEMY_HERO, WEAPON, ENEMY_WEAPON, HAND, ENEMY_HAND, FIELD,
            ENEMY_FIELD)
#else
enum class EntityType
{
    EMPTY,
    SOURCE,
    TARGET,
    FRIENDS,
    ENEMIES,
    HERO,
    ENEMY_HERO,
    WEAPON,
    ENEMY_WEAPON,
    HAND,
    ENEMY_HAND,
    FIELD,
    ENEMY_FIELD
};
#endif
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASK_ENUMS_HPP