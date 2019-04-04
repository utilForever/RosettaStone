// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TASK_ENUMS_HPP
#define ROSETTASTONE_TASK_ENUMS_HPP

#ifdef _MSC_VER
#define ROSETTASTONE_EXPAND_LARGE_ENUMS
#else  // _MSC_VER
#undef BETTER_ENUMS_MACRO_FILE
#define BETTER_ENUMS_MACRO_FILE "Rosetta/Commons/EnumMacros.hpp"
#endif  // _MSC_VER

#include <better-enums/enum.h>

namespace RosettaStone
{
//! \brief An enumerator for identifying each task.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(TaskID, int, INVALID, DRAW, DRAW_OP, OVERDRAW, MODIFY_MANA, DAMAGE,
            MULLIGAN, PLAY_CARD, ADD_ENCHANTMENT, DESTROY, DISCARD, HEAL_FULL,
            POISONOUS, FREEZE, HEAL, INCLUDE, CONTROL, END_TURN, CHOOSE, ATTACK,
            SET_GAME_TAG, ENQUEUE, RANDOM, SUMMON, TRANSFORM, CONDITION);
#else
enum class TaskID
{
    INVALID,
    DRAW,
    DRAW_OP,
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
    ATTACK,
    SET_GAME_TAG,
    ENQUEUE,
    RANDOM,
    SUMMON,
    TRANSFORM,
    CONDITION,
};
#endif

//! \brief An enumerator for identifying entity type.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(EntityType, int, EMPTY, SOURCE, TARGET, ALL, FRIENDS, ENEMIES, HERO,
            ENEMY_HERO, WEAPON, ENEMY_WEAPON, HAND, ENEMY_HAND, ALL_MINIONS,
            MINIONS, ENEMY_MINIONS, STACK)
#else
enum class EntityType
{
    EMPTY,
    SOURCE,
    TARGET,
    ALL,
    FRIENDS,
    ENEMIES,
    HERO,
    ENEMY_HERO,
    WEAPON,
    ENEMY_WEAPON,
    HAND,
    ENEMY_HAND,
    ALL_MINIONS,
    MINIONS,
    ENEMY_MINIONS,
    STACK
};
#endif
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_ENUMS_HPP
