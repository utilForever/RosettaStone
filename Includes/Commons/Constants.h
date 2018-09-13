#ifndef HEARTHSTONEPP_CONSTANTS_H
#define HEARTHSTONEPP_CONSTANTS_H

#include <cstddef>

namespace Hearthstonepp
{
    //! Hearthstone++ version.
    constexpr float VERSION = 0.3f;

    //! The number of player class.
    //! \note Druid, Hunter, Mage, Paladin, Priest, Rogue, Shaman, Warlock, Warrior
    constexpr std::size_t NUM_PLAYER_CLASS = 9;

    //! The maximum number of cards that can be stored in the deck.
    //! \note A deck is a collection of exactly 30 cards.
    constexpr std::size_t MAXIMUM_NUM_CARDS_IN_DECK = 30;

    //! The maximum number of minions that can be placed in the field.
    //! \note Each player can normally have a maximum of 7 minions on the battlefield at any time.
    constexpr std::size_t FIELD_SIZE = 7;

    //! The number of cards at the start of each game to whichever player is selected to go first.
    //! \note The initial hand and mulligan at the start of the game also draws 3-4 randomly selected cards.
    constexpr std::size_t NUM_DRAW_CARDS_AT_START = 3;

    //! The number of menus in main phase.
    //! \note We will refactor it soon.
    constexpr std::size_t GAME_MAIN_MENU_SIZE = 3;
    }

#endif