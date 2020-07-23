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
constexpr std::array<CardSet, 9> STANDARD_CARD_SETS = {
    CardSet::CORE,                   // Basic, 2014
    CardSet::EXPERT1,                // Classic, 2014
    CardSet::DEMON_HUNTER_INITIATE,  // Ashes of Outland, 2020
    CardSet::DALARAN,                // Rise of Shadows, 2019
    CardSet::ULDUM,                  // Saviors of Uldum, 2019
    CardSet::DRAGONS,                // Descent of Dragons, 2019
    CardSet::YEAR_OF_THE_DRAGON,     // Galakrond's Awakening, 2020
    CardSet::BLACK_TEMPLE,           // Ashes of Outland, 2020
    CardSet::SCHOLOMANCE             // Scholomance Academy, 2020
};

//! Specifies which card sets combine into the WILD set.
constexpr std::array<CardSet, 24> WILD_CARD_SETS = {
    // Standard
    CardSet::CORE,                   // Basic, 2014
    CardSet::EXPERT1,                // Classic, 2014
    CardSet::DEMON_HUNTER_INITIATE,  // Ashes of Outland, 2020
    CardSet::DALARAN,                // Rise of Shadows, 2019
    CardSet::ULDUM,                  // Saviors of Uldum, 2019
    CardSet::DRAGONS,                // Descent of Dragons, 2019
    CardSet::YEAR_OF_THE_DRAGON,     // Galakrond's Awakening, 2020
    CardSet::BLACK_TEMPLE,           // Ashes of Outland, 2020
    CardSet::SCHOLOMANCE,            // Scholomance Academy, 2020

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
constexpr int NUM_ALL_CARDS = 9344;

//! The number of Battlegrounds cards.
constexpr int NUM_BATTLEGROUNDS_CARDS = 527;

//! The number of player class.
//! \note Druid, Hunter, Mage, Paladin, Priest, Rogue, Shaman, Warlock, Warrior,
//! Demon Hunter
constexpr int NUM_PLAYER_CLASS = 10;

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

//! The number of players in Battlegrounds.
constexpr int NUM_BATTLEGROUNDS_PLAYERS = 8;

//! The number of heroes in Battlegrounds.
constexpr int NUM_BATTLEGROUNDS_HEROES = 44;

//! The number of heroes on the selection list in Battlegrounds.
constexpr int NUM_HEROES_ON_SELECTION_LIST = 4;

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
constexpr int NUM_TIER1_MINIONS = 16;

//! The number of tier 2 minions in Battlegrounds.
constexpr int NUM_TIER2_MINIONS = 20;

//! The number of tier 3 minions in Battlegrounds.
constexpr int NUM_TIER3_MINIONS = 23;

//! The number of tier 4 minions in Battlegrounds.
constexpr int NUM_TIER4_MINIONS = 19;

//! The number of tier 5 minions in Battlegrounds.
constexpr int NUM_TIER5_MINIONS = 17;

//! The number of tier 6 minions in Battlegrounds.
constexpr int NUM_TIER6_MINIONS = 14;

//! A list of Tier 1 minion dbfIDs in Battlegrounds.
// Alleycat (40426)
// Deck Swabbie (61055)
// Dragonspawn Lieutenant (60628)
// Fiendish Servant (56112)
// Mecharoo (48886)
// Micro Machine (60055)
// Murloc Tidecaller (475)
// Murloc Tidehunter (976)
// Red Whelp (59968)
// Righteous Protector (42467)
// Rockpool Hunter (41245)
// Scallywag (61061)
// Scavenging Hyena (1281)
// Selfless Hero (38740)
// Vulgar Homunculus (43121)
// Wrath Weaver (59670)
constexpr std::array<int, NUM_TIER1_MINIONS> TIER1_MINIONS = {
    40426, 61055, 60628, 56112, 48886, 60055, 475,   976,
    59968, 42467, 41245, 61061, 1281,  38740, 43121, 59670
};

//! A list of Tier 2 minion dbfIDs in Battlegrounds.
// Arcane Cannon (62188)
// Freedealing Gambler (61049)
// Glyph Guardian (61029)
// Harvest Golem (778)
// Imprisoner (59937)
// Kaboom Bot (49279)
// Kindly Grandmother (39481)
// Metaltooth Leaper (2016)
// Murloc Warleader (1063)
// Nathrezim Overseer (59186)
// Old Murk-Eye (736)
// Pogo-Hopper (60122)
// Rabid Saurolisk (62162)
// Rat Pack (40428)
// Southsea Captain (680)
// Spawn of N'Zoth (38797)
// Steward of Time (60621)
// Unstable Ghoul (1808)
// Waxrider Togwaggle (60559)
// Zoobot (39839)
constexpr std::array<int, NUM_TIER2_MINIONS> TIER2_MINIONS = {
    62188, 61049, 61029, 778,   59937, 49279, 39481, 2016, 1063,  59186,
    736,   60122, 62162, 40428, 680,   38797, 60621, 1808, 60559, 39839
};

//! A list of Tier 3 minion dbfIDs in Battlegrounds.
// Bloodsail Cannoneer (61053)
// Bronze Warden (60558)
// Coldlight Seer (453)
// Crystalweaver (40391)
// Crowd Favorite (2518)
// Deflect-o-Bot (61930)
// Felfin Navigator (56393)
// Hangry Dragon (60552)
// Houndmaster (1003)
// Imp Gang Boss (2288)
// Infested Wolf (38734)
// Khadgar (52502)
// Monstrous Macaw (62230)
// Pack Leader (59940)
// Piloted Shredder (60048)
// Replicating Menace (48536)
// Salty Looter (62734)
// Screwjank Clunker (2023)
// Shifter Zerus (57742)
// Soul Juggler (59660)
// The Beast (962)
// Twilight Emissary (60626)
// Yo-Ho-Ogre (61060)
constexpr std::array<int, NUM_TIER3_MINIONS> TIER3_MINIONS = {
    61053, 60558, 453,   40391, 2518,  61930, 56393, 60552,
    1003,  2288,  38734, 52502, 62230, 59940, 60048, 48536,
    62734, 2023,  57742, 59660, 962,   60626, 61060
};

//! A list of Tier 4 minion dbfIDs in Battlegrounds.
// Annoy-o-Module (48993)
// Bolvar, Fireblood (45392)
// Cave Hydra (43358)
// Cobalt Scalebane (42442)
// Defender of Argus (763)
// Drakonid Enforcer (61072)
// Floating Watcher (2068)
// Goldgrubber (61066)
// Herald of Flame (60498)
// Iron Sensei (1992)
// Mechano-Egg (49169)
// Menagerie Magician (39269)
// Ripsnarl Captain (61056)
// Savannah Highmane (1261)
// Security Rover (48100)
// Siegebreaker (54835)
// Southsea Strongarm (61048)
// Toxfin (52277)
// Virmen Sensei (40641)
constexpr std::array<int, NUM_TIER4_MINIONS> TIER4_MINIONS = {
    48993, 45392, 43358, 42442, 763,   61072, 2068,  61066, 60498, 1992,
    49169, 39269, 61056, 1261,  48100, 54835, 61048, 52277, 40641
};

//! A list of Tier 5 minion dbfIDs in Battlegrounds.
// Annihilan Battlemaster (59714)
// Baron Rivendare (1915)
// Brann Bronzebeard (2949)
// Cap'n Hoggarr (61989)
// Ironhide Direhorn (49973)
// Junkbot (2074)
// King Bagurgle (60247)
// Lightfang Enforcer (59707)
// Mal'Ganis (1986)
// Murozond (60637)
// Nat Pagle, Extreme Angler (61046)
// Primalfin Lookout (60028)
// Razorgore, the Untamed (60561)
// Seabreaker Goliath (62458)
// Sneed's Old Shredder (59682)
// Strongshell Scavenger (43022)
// Voidlord (46056)
constexpr std::array<int, NUM_TIER5_MINIONS> TIER5_MINIONS = {
    59714, 1915,  2949,  61989, 49973, 2074,  60247, 59707, 1986,
    60637, 61046, 60028, 60561, 62458, 59682, 43022, 46056
};

//! A list of Tier 6 minion dbfIDs in Battlegrounds.
// Amalgadon (61444)
// Dread Admiral Eliza (61047)
// Foe Reaper 4000 (2081)
// Goldrinn, the Great Wolf (59955)
// Kangor's Apprentice (59935)
// Gentle Megasaur (56465)
// Ghastcoiler (52041)
// Imp Mama (61028)
// Kalecgos, Arcane Aspect (60630)
// Maexxna (1791)
// Mama Bear (60036)
// Nadina the Red (60629)
// The Tide Razor (62232)
// Zapp Slywick (60040)
constexpr std::array<int, NUM_TIER6_MINIONS> TIER6_MINIONS = {
    61444, 61047, 2081, 59955, 59935, 56465, 52041,
    61028, 60630, 1791, 60036, 60629, 62232, 60040
};

//! The total number of tier minions in Battlegrounds Tavern.
constexpr int NUM_TOTAL_TAVERN_MINIONS =
    NUM_TIER1_MINIONS * NUM_COPIES_OF_EACH_TIER1_MINIONS +
    NUM_TIER2_MINIONS * NUM_COPIES_OF_EACH_TIER2_MINIONS +
    NUM_TIER3_MINIONS * NUM_COPIES_OF_EACH_TIER3_MINIONS +
    NUM_TIER4_MINIONS * NUM_COPIES_OF_EACH_TIER4_MINIONS +
    NUM_TIER5_MINIONS * NUM_COPIES_OF_EACH_TIER5_MINIONS +
    NUM_TIER6_MINIONS * NUM_COPIES_OF_EACH_TIER6_MINIONS;

//! A list of races in Battlegrounds.
constexpr std::array<Race, 6> RACES_IN_BATTLEGROUNDS = {
    Race::BEAST,  Race::MECHANICAL, Race::DEMON,
    Race::DRAGON, Race::MURLOC,     Race::PIRATE
};

//! The number of coin to purchase a minion.
constexpr int NUM_COIN_PURCHASE_MINION = 3;

//! The initial number of coin to upgrade Tavern to Tier 2.
constexpr int NUM_COIN_UPGRADE_TAVERN_TIER_2 = 5;

//! The initial number of coin to upgrade Tavern to Tier 3.
constexpr int NUM_COIN_UPGRADE_TAVERN_TIER_3 = 7;

//! The initial number of coin to upgrade Tavern to Tier 4.
constexpr int NUM_COIN_UPGRADE_TAVERN_TIER_4 = 8;

//! The initial number of coin to upgrade Tavern to Tier 5.
constexpr int NUM_COIN_UPGRADE_TAVERN_TIER_5 = 9;

//! The initial number of coin to upgrade Tavern to Tier 6.
constexpr int NUM_COIN_UPGRADE_TAVERN_TIER_6 = 10;

//! The number of coin to refresh Tavern's field.
constexpr int NUM_COIN_REFRESH_TAVERN = 1;

//! The maximum number of tier.
constexpr int TIER_UPPER_LIMIT = 6;

//! The maximum number of coin.
constexpr int COIN_UPPER_LIMIT = 10;

//! The number of menus in main phase.
//! \note We will refactor it soon.
constexpr int GAME_MAIN_MENU_SIZE = 3;
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CONSTANTS_HPP
