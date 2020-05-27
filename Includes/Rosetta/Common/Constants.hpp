// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CONSTANTS_HPP
#define ROSETTASTONE_CONSTANTS_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

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
constexpr std::array<CardSet, 7> STANDARD_CARD_SETS = {
    CardSet::CORE,                // Basic, 2014
    CardSet::EXPERT1,             // Classic, 2014
    CardSet::DALARAN,             // Rise of Shadows, 2019
    CardSet::ULDUM,               // Saviors of Uldum, 2019
    CardSet::DRAGONS,             // Descent of Dragons, 2019
    CardSet::YEAR_OF_THE_DRAGON,  // Galakrond's Awakening, 2020
    CardSet::BLACK_TEMPLE,        // Ashes of Outland, 2020
};

//! Specifies which card sets combine into the WILD set.
constexpr std::array<CardSet, 22> WILD_CARD_SETS = {
    // Standard
    CardSet::CORE,                // Basic, 2014
    CardSet::EXPERT1,             // Classic, 2014
    CardSet::DALARAN,             // Rise of Shadows, 2019
    CardSet::ULDUM,               // Saviors of Uldum, 2019
    CardSet::DRAGONS,             // Descent of Dragons, 2019
    CardSet::YEAR_OF_THE_DRAGON,  // Galakrond's Awakening, 2020
    CardSet::BLACK_TEMPLE,        // Ashes of Outland, 2020

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
    CardSet::GILNEAS,       // The Witchwood, 2018
    CardSet::BOOMSDAY,      // The Boomsday Project, 2018
    CardSet::TROLL,         // Rastakhan's Rumble, 2018
};

//! The number of all cards.
constexpr int NUM_ALL_CARDS = 9057;

//! The number of Battlegrounds cards.
constexpr int NUM_BATTLEGROUNDS_CARDS = 447;

//! The number of player class.
//! \note Druid, Hunter, Mage, Paladin, Priest, Rogue, Shaman, Warlock, Warrior,
//! Demon Hunter
constexpr int NUM_PLAYER_CLASS = 10;

//! The number of heroes in Battlegrounds.
constexpr int NUM_HEROES_IN_BATTLEGROUNDS = 34;

//! The number of copies of each tier 1 minion.
constexpr int NUM_COPIES_OF_EACH_TIER1_MINIONS = 16;

//! The number of copies of each tier 2 minion.
constexpr int NUM_COPIES_OF_EACH_TIER2_MINIONS = 15;

//! The number of copies of each tier 3 minion.
constexpr int NUM_COPIES_OF_EACH_TIER3_MINIONS = 13;

//! The number of copies of each tier 4 minion.
constexpr int NUM_COPIES_OF_EACH_TIER4_MINIONS = 11;

//! The number of copies of each tier 5 minion.
constexpr int NUM_COPIES_OF_EACH_TIER5_MINIONS = 9;

//! The number of copies of each tier 6 minion.
constexpr int NUM_COPIES_OF_EACH_TIER6_MINIONS = 7;

//! The number of tier 1 minions in Battlegrounds.
constexpr int NUM_TIER1_MINIONS = 14;

//! The number of tier 2 minions in Battlegrounds.
constexpr int NUM_TIER2_MINIONS = 17;

//! The number of tier 3 minions in Battlegrounds.
constexpr int NUM_TIER3_MINIONS = 19;

//! The number of tier 4 minions in Battlegrounds.
constexpr int NUM_TIER4_MINIONS = 16;

//! The number of tier 5 minions in Battlegrounds.
constexpr int NUM_TIER5_MINIONS = 15;

//! The number of tier 6 minions in Battlegrounds.
constexpr int NUM_TIER6_MINIONS = 11;

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
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_CONSTANTS_HPP
