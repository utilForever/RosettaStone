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
constexpr std::array<CardSet, 6> STANDARD_CARD_SETS = {
    CardSet::CORE,            // Core, 2021
    CardSet::BLACK_TEMPLE,    // Ashes of Outland, 2020
    CardSet::SCHOLOMANCE,     // Scholomance Academy, 2020
    CardSet::DARKMOON_FAIRE,  // Madness at the Darkmoon Faire, 2020
    CardSet::THE_BARRENS,     // Forged in the Barrens, 2021
    CardSet::STORMWIND,       // United in Stormwind, 2021
};

//! Specifies which card sets combine into the WILD set.
constexpr std::array<CardSet, 28> WILD_CARD_SETS = {
    CardSet::EXPERT1,                // Classic, 2014
    CardSet::LEGACY,                 // Legacy, 2021
    CardSet::NAXX,                   // Curse of Naxxramas, 2014
    CardSet::GVG,                    // Goblins vs Gnomes, 2014
    CardSet::BRM,                    // Blackrock Mountain, 2015
    CardSet::TGT,                    // The Grand Tournament, 2015
    CardSet::LOE,                    // The League of Explorers, 2015
    CardSet::OG,                     // Whispers of the Old Gods, 2016
    CardSet::KARA,                   // One Night in Karazhan, 2016
    CardSet::GANGS,                  // Mean Streets of Gadgetzan, 2016
    CardSet::UNGORO,                 // Journey to Un'Goro, 2017
    CardSet::ICECROWN,               // Knights of the Frozen Throne, 2017
    CardSet::LOOTAPALOOZA,           // Kobolds & Catacombs, 2017
    CardSet::GILNEAS,                // The Witchwood, 2018
    CardSet::BOOMSDAY,               // The Boomsday Project, 2018
    CardSet::TROLL,                  // Rastakhan's Rumble, 2018
    CardSet::DALARAN,                // Rise of Shadows, 2019
    CardSet::ULDUM,                  // Saviors of Uldum, 2019
    CardSet::DRAGONS,                // Descent of Dragons, 2019
    CardSet::YEAR_OF_THE_DRAGON,     // Galakrond's Awakening, 2020
    CardSet::DEMON_HUNTER_INITIATE,  // Ashes of Outland, 2020
    CardSet::BLACK_TEMPLE,           // Ashes of Outland, 2020
    CardSet::SCHOLOMANCE,            // Scholomance Academy, 2020
    CardSet::DARKMOON_FAIRE,         // Madness at the Darkmoon Faire, 2020
    CardSet::THE_BARRENS,            // Forged in the Barrens, 2021
    CardSet::STORMWIND,              // United in Stormwind, 2021
};

//! Specifies which card sets combine into the CLASSIC set.
constexpr std::array<CardSet, 1> CLASSIC_CARD_SETS = {
    CardSet::VANILLA,  // Classic, 2021
};

//! The number of all cards.
constexpr int NUM_ALL_CARDS = 13755;

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
constexpr int NUM_BATTLEGROUNDS_HEROES = 67;

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
constexpr int NUM_TIER1_MINIONS = 19;

//! The number of tier 2 minions in Battlegrounds.
constexpr int NUM_TIER2_MINIONS = 26;

//! The number of tier 3 minions in Battlegrounds.
constexpr int NUM_TIER3_MINIONS = 30;

//! The number of tier 4 minions in Battlegrounds.
constexpr int NUM_TIER4_MINIONS = 26;

//! The number of tier 5 minions in Battlegrounds.
constexpr int NUM_TIER5_MINIONS = 26;

//! The number of tier 6 minions in Battlegrounds.
constexpr int NUM_TIER6_MINIONS = 17;

//! A list of Tier 1 minion dbfIDs in Battlegrounds.
// Beast Pool
// Alleycat (40426)
// Scavenging Hyena (1281)
// Demon Pool
// Fiendish Servant (56112)
// Vulgar Homunculus (43121)
// Wrath Weaver (59670)
// Dragon Pool
// Dragonspawn Lieutenant (60628)
// Red Whelp (59968)
// Elemental Pool
// Refreshing Anomaly (64042)
// Sellemental (64038)
// Mech Pool
// Micro Machine (60055)
// Micro Mummy (53445)
// Murloc Pool
// Murloc Tidecaller (475)
// Murloc Tidehunter (976)
// Rockpool Hunter (41245)
// Pirate Pool
// Deck Swabbie (61055)
// Scallywag (61061)
// Quilboar Pool
// Razorfen Geomancer (70143)
// Sun-Bacon Relaxer (70147)
// Neutral
// Acolyte of C'Thun (63614)
constexpr std::array<int, NUM_TIER1_MINIONS> TIER1_MINIONS = {
    40426, 1281, 56112, 43121, 59670, 60628, 59968, 64042, 64038, 60055,
    53445, 475,  976,   41245, 61055, 61061, 70143, 70147, 63614
};

//! A list of Tier 2 minion dbfIDs in Battlegrounds.
// Beast Pool
// Kindly Grandmother (39481)
// Pack Leader (59940)
// Rabid Saurolisk (62162)
// Demon Pool
// Imprisoner (59937)
// Nathrezim Overseer (59186)
// Dragon Pool
// Glyph Guardian (61029)
// Steward of Time (60621)
// Waxrider Togwaggle (60559)
// Elemental Pool
// Molten Rock (64296)
// Party Elemental (64056)
// Mech Pool
// Harvest Golem (778)
// Kaboom Bot (49279)
// Metaltooth Leaper (2016)
// Murloc Pool
// Murloc Warleader (1063)
// Old Murk-Eye (736)
// Pirate Pool
// Freedealing Gambler (61049)
// Southsea Captain (680)
// Yo-Ho-Ogre (61060)
// Quilboar Pool
// Roadboar (70157)
// Tough Tusk (70162)
// Prophet of the Boar (70153)
// Neutral
// Menagerie Mug (63435)
// Spawn of N'Zoth (38797)
// Selfless Hero (38740)
// Tormented Ritualist (65661)
// Unstable Ghoul (1808)
constexpr std::array<int, NUM_TIER2_MINIONS> TIER2_MINIONS = {
    39481, 59940, 62162, 59937, 59186, 61029, 60621, 60559, 64296,
    64056, 778,   49279, 2016,  1063,  736,   61049, 680,   61060,
    70157, 70162, 70153, 63435, 38797, 38740, 65661, 1808
};

//! A list of Tier 3 minion dbfIDs in Battlegrounds.
// Beast Pool
// Infested Wolf (38734)
// Monstrous Macaw (62230)
// Houndmaster (1003)
// Rat Pack (40428)
// Demon Pool
// Imp Gang Boss (2288)
// Crystalweaver (40391)
// Soul Devourer (61059)
// Soul Juggler (59660)
// Dragon Pool
// Bronze Warden (60558)
// Hangry Dragon (60552)
// Twilight Emissary (60626)
// Elemental Pool
// Arcane Assistant (64297)
// Crackling Cyclone (64054)
// Stasis Elemental (64069)
// Mech Pool
// Deflect-o-Bot (61930)
// Iron Sensei (1992)
// Screwjank Clunker (2023)
// Replicating Menace (48536)
// Murloc Pool
// Coldlight Seer (453)
// Felfin Navigator (56393)
// Pirate Pool
// Bloodsail Cannoneer (61053)
// Salty Looter (62734)
// Southsea Strongarm (61048)
// Quilboar Pool
// Bristleback Brute (70171)
// Bannerboar (70144)
// Thorncaller (70175)
// Necrolyte (70151)
// Neutral
// Arm of the Empire (63622)
// Khadgar (52502)
// Warden of Old (65660)
constexpr std::array<int, NUM_TIER3_MINIONS> TIER3_MINIONS = {
    38734, 62230, 1003,  40428, 2288,  40391, 61059, 59660, 60558, 60552,
    60626, 64297, 64054, 64069, 61930, 1992,  2023,  48536, 453,   56393,
    61053, 62734, 61048, 70171, 70144, 70175, 70151, 63622, 52502, 65660
};

//! A list of Tier 4 minion dbfIDs in Battlegrounds.
// Beast Pool
// Cave Hydra (43358)
// Savannah Highmane (1261)
// Virmen Sensei (40641)
// Demon Pool
// Bigfernal (66227)
// Hexruin Marauder (73072)
// Ring Matron (61884)
// Dragon Pool
// Cobalt Scalebane (42442)
// Drakonid Enforcer (61072)
// Herald of Flame (60498)
// Elemental Pool
// Majordomo Executus (63630)
// Wildfire Elemental (64189)
// Mech Pool
// Annoy-o-Module (48993)
// Mechano-Egg (49169)
// Security Rover (48100)
// Murloc Pool
// Primalfin Lookout (60028)
// Toxfin (52277)
// Pirate Pool
// Goldgrubber (61066)
// Ripsnarl Captain (61056)
// Quilboar Pool
// Dynamic Duo (70184)
// Bonker (70173)
// Groundshaker (70188)
// Neutral
// Bolvar, Fireblood (45392)
// Champion of Y'Shaarj (63623)
// Defender of Argus (763)
// Menagerie Jug (63487)
// Qiraji Harbinger (63619)
constexpr std::array<int, NUM_TIER4_MINIONS> TIER4_MINIONS = {
    43358, 1261,  40641, 66227, 73072, 61884, 42442, 61072, 60498,
    63630, 64189, 48993, 49169, 48100, 60028, 52277, 61066, 61056,
    70184, 70173, 70188, 45392, 63623, 763,   63487, 63619
};

//! A list of Tier 5 minion dbfIDs in Battlegrounds.
// Beast Pool
// Ironhide Direhorn (49973)
// Mama Bear (60036)
// Demon Pool
// Annihilan Battlemaster (59714)
// Mal'Ganis (1986)
// Voidlord (46056)
// Dragon Pool
// Murozond (60637)
// Razorgore, the Untamed (60561)
// Elemental Pool
// Nomi, Kitchen Nightmare (63626)
// Tavern Tempest (64077)
// Mech Pool
// Junkbot (2074)
// Kangor's Apprentice (59935)
// Sneed's Old Shredder (59682)
// Murloc Pool
// King Bagurgle (60247)
// Pirate Pool
// Cap'n Hoggarr (61989)
// Nat Pagle, Extreme Angler (61046)
// Seabreaker Goliath (62458)
// Quilboar Pool
// Bristleback Knight (70158)
// Aggem Thorncurse (70163)
// Agamaggan, The Great Boar (70176)
// Neutral
// Baron Rivendare (1915)
// Brann Bronzebeard (2949)
// Deadly Spore (65031)
// Faceless Taverngoer (63627)
// Lightfang Enforcer (59707)
// Mythrax the Unraveler (65662)
// Strongshell Scavenger (43022)
constexpr std::array<int, NUM_TIER5_MINIONS> TIER5_MINIONS = {
    49973, 60036, 59714, 1986,  46056, 60637, 60561, 63626, 64077,
    2074,  59935, 59682, 60247, 61989, 61046, 62458, 70158, 70163,
    70176, 1915,  2949,  65031, 63627, 59707, 65662, 43022
};

//! A list of Tier 6 minion dbfIDs in Battlegrounds.
// Beast Pool
// Ghastcoiler (59687)
// Goldrinn, the Great Wolf (59955)
// Maexxna (1791)
// Demon Pool
// Imp Mama (61028)
// Dragon Pool
// Kalecgos, Arcane Aspect (60630)
// Nadina the Red (60629)
// Elemental Pool
// Gentle Djinni (64062)
// Lieutenant Garr (64081)
// Lil' Rag (63624)
// Mech Pool
// Foe Reaper 4000 (2081)
// Murloc Pool
// N/A
// Pirate Pool
// Dread Admiral Eliza (61047)
// The Tide Razor (62232)
// Quilboar Pool
// Charlga (70165)
// Captain Flat Tusk (70179)
// Neutral
// Amalgadon (61444)
// Archdruid Hamuul (72230)
// Zapp Slywick (60040)
constexpr std::array<int, NUM_TIER6_MINIONS> TIER6_MINIONS = {
    59687, 59955, 1791,  61028, 60630, 60629, 64062, 64081, 63624,
    2081,  61047, 62232, 70165, 70179, 61444, 72230, 60040
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
constexpr std::array<Race, 7> RACES_IN_BATTLEGROUNDS = {
    Race::BEAST,      Race::DEMON,  Race::DRAGON, Race::ELEMENTAL,
    Race::MECHANICAL, Race::MURLOC, Race::PIRATE
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
