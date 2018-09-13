/*************************************************************************
> File Name: Constants.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Constants for Hearthstone++.
> Created Time: 2017/10/08
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CONSTANTS_H
#define HEARTHSTONEPP_CONSTANTS_H

#include <cstddef>

namespace Hearthstonepp
{
    constexpr float VERSION = 0.3f;

    constexpr std::size_t PLAYER_CLASS_SIZE = 9;
    constexpr std::size_t MAXIMUM_NUM_CARDS_IN_DECK = 30;
    constexpr std::size_t FIELD_SIZE = 7;

    constexpr std::size_t NUM_BEGIN_DRAW = 3;
    constexpr std::size_t GAME_MAIN_MENU_SIZE = 3;
    }

#endif