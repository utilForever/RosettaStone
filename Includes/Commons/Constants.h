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
	constexpr float VERSION = 0.1f;

	constexpr std::size_t LOGIN_MENU_SIZE = 3;
	constexpr std::size_t MAIN_MENU_SIZE = 4;
	constexpr std::size_t MANAGE_DECK_MENU_SIZE = 4;
	constexpr std::size_t CREATE_DECK_MENU_SIZE = 3;

	constexpr std::size_t PLAYER_CLASS_SIZE = 9;
	constexpr unsigned int MAXIMUM_NUM_CARDS_IN_DECK = 30;
    constexpr unsigned int FIELD_SIZE = 7;

	constexpr unsigned int NUM_BEGIN_DRAW = 3;

	constexpr size_t GAME_MAIN_MENU_SIZE = 3;
}

#endif