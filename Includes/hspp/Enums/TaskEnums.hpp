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
BETTER_ENUM(TaskID, int, INVALID = 0, TASK_VECTOR = 1, REQUIRE = 2,
            PLAYER_SETTING = 3, SWAP = 4, SHUFFLE = 5, DRAW = 6, OVERDRAW = 7,
            MODIFY_MANA = 8, MODIFY_HEALTH = 9, BRIEF = 10, SELECT_MENU = 11,
            SELECT_CARD = 12, SELECT_TARGET = 13, SELECT_POSITION = 14,
            MULLIGAN = 15, COMBAT = 16, PLAY_CARD = 17, PLAY_MINION = 18,
            PLAY_WEAPON = 19, PLAY_SPELL = 20, GAME_END = 21,
            ADD_ENCHANTMENT = 22, DESTROY = 23, DISCARD = 24, HEAL_FULL = 25,
            POISONOUS = 26, FREEZE = 27, INIT_ATTACK_COUNT = 28, HEAL = 29);
#else
enum class TaskID
{
    INVALID = 0,
    TASK_VECTOR = 1,
    REQUIRE = 2,
    PLAYER_SETTING = 3,
    SWAP = 4,
    SHUFFLE = 5,
    DRAW = 6,
    OVER_DRAW = 7,
    MODIFY_MANA = 8,
    MODIFY_HEALTH = 9,
    BRIEF = 10,
    SELECT_MENU = 11,
    SELECT_CARD = 12,
    SELECT_TARGET = 13,
    SELECT_POSITION = 14,
    MULLIGAN = 15,
    COMBAT = 16,
    PLAY_CARD = 17,
    PLAY_MINION = 18,
    PLAY_WEAPON = 19,
    PLAY_SPELL = 20,
    GAME_END = 21,
    ADD_ENCHANTMENT = 22,
    DESTROY = 23,
    DISCARD = 24,
    HEAL_FULL = 25,
    POISONOUS = 26,
    FREEZE = 27,
    INIT_ATTACK_COUNT = 28,
    HEAL = 29
};
#endif

//! \brief An enumerator for identifying entity type.
#ifndef HEARTHSTONEPP_DOXYGEN
BETTER_ENUM(EntityType, int, EMPTY = 0, SOURCE = 1, TARGET = 2, FRIENDS = 3,
            ENEMIES = 4, HERO = 5, ENEMY_HERO = 6, WEAPON = 7, ENEMY_WEAPON = 8,
            HAND = 9, ENEMY_HAND = 10, FIELD = 11, ENEMY_FIELD = 12)
#else
enum class EntityType
{
    EMPTY = 0,
    SOURCE = 1,
    TARGET = 2,
    FRIENDS = 3,
    ENEMIES = 4,
    HERO = 5,
    ENEMY_HERO = 6,
    WEAPON = 7,
    ENEMY_WEAPON = 8,
    HAND = 9,
    ENEMY_HAND = 10,
    FIELD = 11,
    ENEMY_FIELD = 12
};
#endif
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASK_ENUMS_HPP