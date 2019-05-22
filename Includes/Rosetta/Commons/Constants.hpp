// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CONSTANTS_HPP
#define ROSETTASTONE_CONSTANTS_HPP

namespace RosettaStone
{
//! RosettaStone version.
constexpr float VERSION = 0.4f;

//! The number of player class.
//! \note Druid, Hunter, Mage, Paladin, Priest, Rogue, Shaman, Warlock, Warrior
constexpr int NUM_PLAYER_CLASS = 9;

//! The number of cards that can be stored in the deck at game start.
constexpr int START_DECK_SIZE = 30;

//! The maximum number of cards that can be stored in the deck during game.
constexpr int MAX_DECK_SIZE = 60;

//! The maximum number of minions that can be placed in the field.
constexpr int FIELD_SIZE = 7;

//! The number of cards that the player going first will be given.
constexpr int NUM_DRAW_CARDS_AT_START_FIRST = 3;

//! The number of cards that the player going second will be given.
constexpr int NUM_DRAW_CARDS_AT_START_SECOND = 4;

//! The minimum number of available/maximum mana.
constexpr int MANA_LOWER_LIMIT = 0;

//! The maximum number of available/maximum mana.
constexpr int MANA_UPPER_LIMIT = 10;

//! The maximum number of cards in your hand.
constexpr int HAND_SIZE = 10;

// NOTE: 0 means my hero, 1 ~ 7 means my minion in field
//       8 means opponent hero, 9 ~ 15 means opponent minion in field.
//! The index of my hero for targeting when player is played card.
constexpr int INDEX_MY_HERO = 0;

//! The index of my minion for targeting when player is played card.
constexpr int INDEX_MY_MINION = INDEX_MY_HERO + 1;

//! The index of opponent hero for targeting when player is played card.
constexpr int INDEX_OPPONENT_HERO = INDEX_MY_MINION + FIELD_SIZE;

//! The index of opponent minion for targeting when player is played card.
constexpr int INDEX_OPPONENT_MINION = INDEX_OPPONENT_HERO + 1;

//! Enumeration that represents the player.
enum class PlayerType
{
    RANDOM,   //!< The random player.
    PLAYER1,  //!< The first player.
    PLAYER2,  //!< The second player.
};

//! The number of menus in main phase.
//! \note We will refactor it soon.
constexpr int GAME_MAIN_MENU_SIZE = 3;
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CONSTANTS_HPP
