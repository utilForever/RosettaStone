// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CONSTANTS_HPP
#define ROSETTASTONE_CONSTANTS_HPP

#include <Rosetta/Enums/CardEnums.hpp>

#include <array>
#include <string>

namespace RosettaStone
{
//! RosettaStone version.
constexpr float VERSION = 0.4f;

//! Deck code version.
constexpr int DECK_CODE_VERSION = 1;

//! Invalid card ID.
const std::string INVALID_CARD_ID = "INVALID";

//! Specifies which card sets combine into the STANDARD set.
constexpr std::array<CardSet, 9> STANDARD_CARD_SETS = {
    CardSet::CORE,                // Basic, 2014
    CardSet::EXPERT1,             // Classic, 2014
    CardSet::GILNEAS,             // The Witchwood, 2018
    CardSet::BOOMSDAY,            // The Boomsday Project, 2018
    CardSet::TROLL,               // Rastakhan's Rumble, 2018
    CardSet::DALARAN,             // Rise of Shadows, 2019
    CardSet::ULDUM,               // Saviors of Uldum, 2019
    CardSet::DRAGONS,             // Descent of Dragons, 2019
    CardSet::YEAR_OF_THE_DRAGON,  // Galakrond's Awakening, 2020
};

//! Specifies which card sets combine into the WILD set.
constexpr std::array<CardSet, 21> WILD_CARD_SETS = {
    // Standard
    CardSet::CORE,                // Basic, 2014
    CardSet::EXPERT1,             // Classic, 2014
    CardSet::GILNEAS,             // The Witchwood, 2018
    CardSet::BOOMSDAY,            // The Boomsday Project, 2018
    CardSet::TROLL,               // Rastakhan's Rumble, 2018
    CardSet::DALARAN,             // Rise of Shadows, 2019
    CardSet::ULDUM,               // Saviors of Uldum, 2019
    CardSet::DRAGONS,             // Descent of Dragons, 2019
    CardSet::YEAR_OF_THE_DRAGON,  // Galakrond's Awakening, 2020

    // Wild
    CardSet::NAXX,          // Curse of Naxxramas, 2014
    CardSet::GVG,           // Goblins vs Gnomes, 2014
    CardSet::BRM,           // Blackrock Mountain, 2015
    CardSet::TGT,           // The Grand Tournament, 2015
    CardSet::LOE,           // The League of Explorers, 2015
    CardSet::OG,            // Whispers of the Old Gods, 2016
    CardSet::KARA,          // One Night in Karazhan, 2016
    CardSet::GANGS,         // Mean Streets of Gadgetzan, 2016
    CardSet::HOF,           // Hall of Fame, 2017
    CardSet::UNGORO,        // Journey to Un'Goro, 2017
    CardSet::ICECROWN,      // Knights of the Frozen Throne, 2017
    CardSet::LOOTAPALOOZA,  // Kobolds & Catacombs, 2017
};

//! The number of all cards.
constexpr int NUM_ALL_CARDS = 9057;

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
