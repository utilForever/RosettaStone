// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CARD_ENUMS_HPP
#define ROSETTASTONE_CARD_ENUMS_HPP

#ifdef _MSC_VER
#define ROSETTASTONE_EXPAND_LARGE_ENUMS
#else  // _MSC_VER
#undef BETTER_ENUMS_MACRO_FILE
#define BETTER_ENUMS_MACRO_FILE "Rosetta/Commons/EnumMacros.hpp"
#endif  // _MSC_VER

#include <Rosetta/Commons/Utils.hpp>

#include <better-enums/enum.h>

namespace RosettaStone
{
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(BlockType, int, ATTACK = 1, JOUST = 2, POWER = 3, SCRIPT = 4,
            TRIGGER = 5, DEATHS = 6, PLAY = 7, FATIGUE = 8, RITUAL = 9,
            REVEAL_CARD = 10, GAME_RESET = 11, ACTION = 99)

BETTER_ENUM(BattleNetGameType, int, UNKNOWN = 0, FRIENDS = 1,
            RANKED_STANDARD = 2, ARENA = 3, VS_AI = 4, TUTORIAL = 5, ASYNC = 6,
            CASUAL_STANDARD_NEWBIE = 9, CASUAL_STANDARD_NORMAL = 10, TEST1 = 11,
            TEST2 = 12, TEST3 = 13, TAVERNBRAWL_PVP = 16,
            TAVERNBRAWL_1P_VERSUS_AI = 17, TAVERNBRAWL_2P_COOP = 18,
            RANKED_WILD = 30, CASUAL_WILD = 31, FSG_BRAWL_VS_FRIEND = 40,
            FSG_BRAWL_PVP = 41, FSG_BRAWL_1P_VERSUS_AI = 42,
            FSG_BRAWL_2P_COOP = 43, BGT_RANKED_STANDARD_NEW_PLAYER = 45)

BETTER_ENUM(BattleNetRegion, int, UNINITIALIZED = -1, UNKNOWN = 0, US = 1,
            EU = 2, KR = 3, TW = 4, CN = 5, LIVE_VERIFICATION = 40,
            PTR_LOC = 41)

BETTER_ENUM(Booster, int, INVALID = 0, CLASSIC = 1, GOBLINS_VS_GNOMES = 9,
            THE_GRAND_TOURNAMENT = 10, OLD_GODS = 11, FIRST_PURCHASE_OLD = 17,
            SIGNUP_INCENTIVE = 18, MEAN_STREETS = 19, UNGORO = 20,
            FROZEN_THRONE = 21, GOLDEN_CLASSIC_PACK = 23,
            KOBOLDS_AND_CATACOMBS = 30, WITCHWOOD = 31,
            THE_BOOMSDAY_PROJECT = 38, MAMMOTH_BUNDLE = 41,
            FIRST_PURCHASE = 181)

BETTER_ENUM(BrawlType, int, UNKNOWN = 0, TAVERN_BRAWL = 1,
            FIRESIDE_GATHERING = 2, COUNT = 3)
#endif

//! \brief An enumerator for identifying the class of the card.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(CardClass, int, INVALID = 0, DEATHKNIGHT = 1, DRUID = 2, HUNTER = 3,
            MAGE = 4, PALADIN = 5, PRIEST = 6, ROGUE = 7, SHAMAN = 8,
            WARLOCK = 9, WARRIOR = 10, DREAM = 11, NEUTRAL = 12, WHIZBANG = 13)
#else
enum class CardClass
{
    INVALID = 0,
    DEATHKNIGHT = 1,
    DRUID = 2,
    HUNTER = 3,
    MAGE = 4,
    PALADIN = 5,
    PRIEST = 6,
    ROGUE = 7,
    SHAMAN = 8,
    WARLOCK = 9,
    WARRIOR = 10,
    DREAM = 11,
    NEUTRAL = 12,
    WHIZBANG = 13
};
#endif

//! \brief An enumerator for identifying the set of the card.
enum class CardSet
{
#define X(a) a,
#include "CardSet.def"
#undef X
    CardSetCount
};

constexpr const char* CARD_SET_STR[] = {
#define X(a) #a,
#include "CardSet.def"
#undef X
    nullptr
};

//! \brief An enumerator for identifying the type of the card.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(CardType, int, INVALID = 0, GAME = 1, PLAYER = 2, HERO = 3,
            MINION = 4, SPELL = 5, ENCHANTMENT = 6, WEAPON = 7, ITEM = 8,
            TOKEN = 9, HERO_POWER = 10)
#else
enum class CardType
{
    INVALID = 0,
    GAME = 1,
    PLAYER = 2,
    HERO = 3,
    MINION = 4,
    SPELL = 5,
    ENCHANTMENT = 6,
    WEAPON = 7,
    ITEM = 8,
    TOKEN = 9,
    HERO_POWER = 10
};
#endif

//! \brief An enumerator for identifying the set of the card.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(ChoiceType, int, INVALID = 0, MULLIGAN = 1, GENERAL = 2)
#else
enum class ChoiceType
{
    INVALID = 0,
    MULLIGAN = 1,
    GENERAL = 2
};
#endif

#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(DeckType, int, CLIENT_ONLY_DECK = -1, UNKNOWN_DECK_TYPE = 0,
            NORMAL_DECK = 1, AI_DECK = 2, DRAFT_DECK = 4, PRECON_DECK = 5,
            TAVERN_BRAWL_DECK = 6, FSG_BRAWL_DECK = 7,
            FRIENDLY_TOURNAMENT_DECK = 8, HIDDEN_DECK = 1000)

BETTER_ENUM(DungeonRewardOption, int, INVALID = 0, LOOT = 1, TREASURE = 2)

BETTER_ENUM(EnchantmentVisual, int, INVALID = 0, POSITIVE = 1, NEGATIVE = 2,
            NEUTRAL = 3)

BETTER_ENUM(Faction, int, INVALID = 0, HORDE = 1, ALLIANCE = 2, NEUTRAL = 3)

BETTER_ENUM(FormatType, int, UNKNOWN = 0, WILD = 1, STANDARD = 2)
#endif

//! \brief An enumerator for identifying the game tag of the card.
enum class GameTag
{
#define X(a) a,
#include "GameTag.def"
#undef X
    GameTagCount
};

constexpr const char* GAME_TAG_STR[] = {
#define X(a) #a,
#include "GameTag.def"
#undef X
    nullptr
};

#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(GameType, int, UNKNOWN = 0, VS_AI = 1, VS_FRIEND = 2, TUTORIAL = 4,
            ARENA = 5, TEST_AI_VS_AI = 6, RANKED = 7, CASUAL = 8,
            TAVERNBRAWL = 16, TB_1P_VS_AI = 17, TB_2P_COOP = 18,
            FSG_BRAWL_VS_FRIEND = 19, FSG_BRAWL = 20, FSG_BRAWL_1P_VS_AI = 21,
            FSG_BRAWL_2P_COOP = 22, GT_TOURNAMENT = 23)

BETTER_ENUM(GoldRewardState, int, INVALID = 0, ELIGIBLE = 1,
            WRONG_GAME_TYPE = 2, ALREADY_CAPPED = 3, BAD_RATING = 4,
            SHORT_GAME = 5, SHORT_GAME_BY_TIME = 5, OVER_CAIS = 6)

BETTER_ENUM(Locale, int, UNKNOWN = -1, enUS = 0, enGB = 1, frFR = 2, deDE = 3,
            koKR = 4, esES = 5, esMX = 6, ruRU = 7, zhTW = 8, zhCN = 9,
            itIT = 10, ptBR = 11, plPL = 12, ptPT = 13, jaJP = 14, thTH = 15)

BETTER_ENUM(MetaDataType, int, TARGET = 0, DAMAGE = 1, HEALING = 2, JOUST = 3,
            CLIENT_HISTORY = 4, SHOW_BIG_CARD = 5, EFFECT_TIMING = 6,
            HISTORY_TARGET = 7, OVERRIDE_HISTORY = 8,
            HISTORY_TARGET_DONT_DUPLICATE_UNTIL_END = 9,
            BEGIN_ARTIFICIAL_HISTORY_TILE = 10,
            BEGIN_ARTIFICIAL_HISTORY_TRIGGER_TILE = 11,
            END_ARTIFICIAL_HISTORY_TILE = 12, START_DRAW = 13, BURNED_CARD = 14,
            EFFECT_SELECTION = 15, BEGIN_LISTENING_FOR_TURN_EVENTS = 16,
            HOLD_DRAWN_CARD = 17)

BETTER_ENUM(Mulligan, int, INVALID = 0, INPUT = 1, DEALING = 2, WAITING = 3,
            DONE = 4)

BETTER_ENUM(MultiClassGroup, int, INVALID = 0, GRIMY_GOONS = 1, JADE_LOTUS = 2,
            KABAL = 3)

BETTER_ENUM(OptionType, int, PASS = 1, END_TURN = 2, POWER = 3)
#endif

//! \brief An enumerator for identifying the play requirement of the card.
enum class PlayReq
{
#define X(a) a,
#include "PlayReq.def"
#undef X
    PlayReqCount
};

constexpr const char* PLAY_REQ_STR[] = {
#define X(a) #a,
#include "PlayReq.def"
#undef X
    nullptr
};

#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(PlayState, int, INVALID = 0, PLAYING = 1, WINNING = 2, LOSING = 3,
            WON = 4, LOST = 5, TIED = 6, DISCONNECTED = 7, CONCEDED = 8)

BETTER_ENUM(PowerType, int, FULL_ENTITY = 1, SHOW_ENTITY = 2, HIDE_ENTITY = 3,
            TAG_CHANGE = 4, BLOCK_START = 5, ACTION_START = 5, BLOCK_END = 6,
            ACTION_END = 6, CREATE_GAME = 7, META_DATA = 8, CHANGE_ENTITY = 9,
            RESET_GAME = 10)
#endif

//! \brief An enumerator for identifying the race of the card.
enum class Race
{
#define X(a) a,
#include "Race.def"
#undef X
    RaceCount
};

constexpr const char* RACE_STR[] = {
#define X(a) #a,
#include "Race.def"
#undef X
    nullptr
};

//! \brief An enumerator for identifying the rarity of the card.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(Rarity, int, INVALID = 0, COMMON = 1, FREE = 2, RARE = 3, EPIC = 4,
            LEGENDARY = 5, UNKNOWN_6 = 6)
#else
enum class Rarity
{
    INVALID = 0,
    COMMON = 1,
    FREE = 2,
    RARE = 3,
    EPIC = 4,
    LEGENDARY = 5,
    UNKNOWN_6 = 6
};
#endif

#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(State, int, INVALID = 0, LOADING = 1, RUNNING = 2, COMPLETE = 3)
#endif

//! \brief An enumerator for indicating the game state.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(Step, int, INVALID = 0, BEGIN_FIRST = 1, BEGIN_SHUFFLE = 2,
            BEGIN_DRAW = 3, BEGIN_MULLIGAN = 4, MAIN_BEGIN = 5, MAIN_READY = 6,
            MAIN_RESOURCE = 7, MAIN_DRAW = 8, MAIN_START = 9, MAIN_ACTION = 10,
            MAIN_COMBAT = 11, MAIN_END = 12, MAIN_NEXT = 13, FINAL_WRAPUP = 14,
            FINAL_GAMEOVER = 15, MAIN_CLEANUP = 16, MAIN_START_TRIGGERS = 17)
#else
enum class Step
{
    INVALID = 0,
    BEGIN_FIRST = 1,
    BEGIN_SHUFFLE = 2,
    BEGIN_DRAW = 3,
    BEGIN_MULLIGAN = 4,
    MAIN_BEGIN = 5,
    MAIN_READY = 6,
    MAIN_RESOURCE = 7,
    MAIN_DRAW = 8,
    MAIN_START = 9,
    MAIN_ACTION = 10,
    MAIN_COMBAT = 11,
    MAIN_END = 12,
    MAIN_NEXT = 13,
    FINAL_WRAPUP = 14,
    FINAL_GAMEOVER = 15,
    MAIN_CLEANUP = 16,
    MAIN_START_TRIGGERS = 17
};
#endif

#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(Type, int, LOCSTRING = -2, UNKNOWN = 0, BOOL = 1, NUMBER = 2,
            COUNTER = 3, ENTITY = 4, PLAYER = 5, TEAM = 6,
            ENTITY_DEFINITION = 7, STRING = 8)

BETTER_ENUM(ZodiacYear, int, INVALID = -1, PRE_STANDARD = 0, KRAKEN = 1,
            MAMMOTH = 2, RAVEN = 3)

BETTER_ENUM(Zone, int, INVALID = 0, PLAY = 1, DECK = 2, HAND = 3, GRAVEYARD = 4,
            REMOVEDFROMGAME = 5, SETASIDE = 6, SECRET = 7)
#endif

template <class T>
T StrToEnum(const char*);
template <class T>
const char* EnumToStr(T);

#define STR2ENUM(TYPE, ARRAY)                                        \
    template <>                                                      \
    inline TYPE StrToEnum<TYPE>(const char* str)                     \
    {                                                                \
        for (int i = 0; i < (sizeof(ARRAY) / sizeof(ARRAY[0])); i++) \
            if (!strcmp(ARRAY[i], str))                              \
                return TYPE(i);                                      \
        return TYPE(0);                                              \
    }

#define ENUM2STR(TYPE, ARRAY)                  \
    template <>                                \
    inline const char* EnumToStr<TYPE>(TYPE v) \
    {                                          \
        return ARRAY[static_cast<int>(v)];     \
    }

#define ENUM_AND_STR(TYPE, ARRAY) \
    STR2ENUM(TYPE, ARRAY)         \
    ENUM2STR(TYPE, ARRAY)

ENUM_AND_STR(CardSet, CARD_SET_STR)
ENUM_AND_STR(GameTag, GAME_TAG_STR)
ENUM_AND_STR(PlayReq, PLAY_REQ_STR)
ENUM_AND_STR(Race, RACE_STR)
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_ENUMS_HPP
