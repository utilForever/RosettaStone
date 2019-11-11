// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CONSTANTS_HPP
#define ROSETTASTONE_CONSTANTS_HPP

#include <string>

namespace RosettaStone
{
//! RosettaStone version.
constexpr float VERSION = 0.4f;

//! Deck code version.
constexpr int DECK_CODE_VERSION = 1;

//! Invalid card ID.
const std::string INVALID_CARD_ID = "INVALID";

//! The number of player class.
//! \note Druid, Hunter, Mage, Paladin, Priest, Rogue, Shaman, Warlock, Warrior
constexpr int NUM_PLAYER_CLASS = 9;

//! The number of cards that can be stored in the deck at game start.
constexpr int START_DECK_SIZE = 30;

//! The maximum number of cards that can be stored in the deck during game.
constexpr int MAX_DECK_SIZE = 60;

//! The maximum number of minions that can be placed in the field.
constexpr int MAX_FIELD_SIZE = 7;

//! The number of cards that the player going first will be given.
constexpr int NUM_DRAW_CARDS_AT_START_FIRST = 3;

//! The number of cards that the player going second will be given.
constexpr int NUM_DRAW_CARDS_AT_START_SECOND = 4;

//! The minimum number of available/maximum mana.
constexpr int MANA_LOWER_LIMIT = 0;

//! The maximum number of available/maximum mana.
constexpr int MANA_UPPER_LIMIT = 10;

//! The maximum number of cards in your hand.
constexpr int MAX_HAND_SIZE = 10;

//! The maximum number of secrets in secret zone.
constexpr int MAX_SECERT_SIZE = 5;

//! The number of menus in main phase.
//! \note We will refactor it soon.
constexpr int GAME_MAIN_MENU_SIZE = 3;
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CONSTANTS_HPP
