/*************************************************************************
> File Name: TaskEnums.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Enumerations for task.
> Created Time: 2018/07/01
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_TASK_ENUMS_H
#define HEARTHSTONEPP_TASK_ENUMS_H

#ifdef _MSC_VER
#define HEARTHSTONEPP_EXPAND_LARGE_ENUMS
#else  // _MSC_VER
#undef BETTER_ENUMS_MACRO_FILE
#define BETTER_ENUMS_MACRO_FILE "../../Includes/Enums/EnumMacros.h"
#endif  // _MSC_VER

#include <better-enums/enum.h>

namespace Hearthstonepp
{
BETTER_ENUM(TaskID, int, INVALID = 0, TASK_VECTOR = 1, REQUIRE = 2,
            PLAYER_SETTING = 3, SWAP = 4, SHUFFLE = 5, DRAW = 6, OVER_DRAW = 7,
            MODIFY_MANA = 8, MODIFY_HEALTH = 9, BRIEF = 10, SELECT_MENU = 11,
            SELECT_CARD = 12, SELECT_TARGET = 13, SELECT_POSITION = 14,
            MULLIGAN = 15, COMBAT = 16, PLAY_CARD = 17, PLAY_MINION = 18,
            PLAY_WEAPON = 19, PLAY_SPELL = 20, GAME_END = 21, ADD_ENCHANTMENT = 22,
            DESTROY = 23, DISCARD = 24, HEAL_FULL = 25, POISONOUS = 26, FREEZE = 27, INIT_ATTACK_COUNT = 28, HEAL = 29)

BETTER_ENUM(EntityType, int, EMPTY = 0, TARGET = 1, OPPONENT_WEAPON = 2, MY_HAND = 3, MY_HERO = 4)

BETTER_ENUM(TargetType, int, INVALID = 0, MY_HERO = 1, MY_FIELD = 2,
            OPPONENT_HERO = 3, OPPONENT_FIELD = 4);
}  // namespace Hearthstonepp

#endif