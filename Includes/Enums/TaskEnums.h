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
BETTER_ENUM(PowerTaskType, int, EMPTY = 0, DESTROY_OPPONENT_WEAPON = 1,
            HEAL_FULL = 2)

BETTER_ENUM(TargetType, int, INVALID = 0, MY_HERO = 1, MY_FIELD = 2,
            OPPONENT_HERO = 3, OPPONENT_FIELD = 4);
}

#endif