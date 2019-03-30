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
#if !defined(ROSETTASTONE_EXPAND_LARGE_ENUMS) && !defined(ROSETTASTONE_DOXYGEN)
BETTER_ENUM(
    PlayReq, int, INVALID = -1, REQ_MINION_TARGET = 1, REQ_FRIENDLY_TARGET = 2,
    REQ_ENEMY_TARGET = 3, REQ_DAMAGED_TARGET = 4, REQ_MAX_SECRETS = 5,
    REQ_FROZEN_TARGET = 6, REQ_CHARGE_TARGET = 7, REQ_TARGET_MAX_ATTACK = 8,
    REQ_NONSELF_TARGET = 9, REQ_TARGET_WITH_RACE = 10, REQ_TARGET_TO_PLAY = 11,
    REQ_NUM_MINION_SLOTS = 12, REQ_WEAPON_EQUIPPED = 13, REQ_ENOUGH_MANA = 14,
    REQ_YOUR_TURN = 15, REQ_NONSTEALTH_ENEMY_TARGET = 16, REQ_HERO_TARGET = 17,
    REQ_SECRET_ZONE_CAP = 18, REQ_MINION_CAP_IF_TARGET_AVAILABLE = 19,
    REQ_MINION_CAP = 20, REQ_TARGET_ATTACKED_THIS_TURN = 21,
    REQ_TARGET_IF_AVAILABLE = 22, REQ_MINIMUM_ENEMY_MINIONS = 23,
    REQ_TARGET_FOR_COMBO = 24, REQ_NOT_EXHAUSTED_ACTIVATE = 25,
    REQ_UNIQUE_SECRET_OR_QUEST = 26, REQ_TARGET_TAUNTER = 27,
    REQ_CAN_BE_ATTACKED = 28, REQ_ACTION_PWR_IS_MASTER_PWR = 29,
    REQ_TARGET_MAGNET = 30, REQ_ATTACK_GREATER_THAN_0 = 31,
    REQ_ATTACKER_NOT_FROZEN = 32, REQ_HERO_OR_MINION_TARGET = 33,
    REQ_CAN_BE_TARGETED_BY_SPELLS = 34, REQ_SUBCARD_IS_PLAYABLE = 35,
    REQ_TARGET_FOR_NO_COMBO = 36, REQ_NOT_MINION_JUST_PLAYED = 37,
    REQ_NOT_EXHAUSTED_HERO_POWER = 38, REQ_CAN_BE_TARGETED_BY_OPPONENTS = 39,
    REQ_ATTACKER_CAN_ATTACK = 40, REQ_TARGET_MIN_ATTACK = 41,
    REQ_CAN_BE_TARGETED_BY_HERO_POWERS = 42, REQ_ENEMY_TARGET_NOT_IMMUNE = 43,
    REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 44, REQ_MINIMUM_TOTAL_MINIONS = 45,
    REQ_MUST_TARGET_TAUNTER = 46, REQ_UNDAMAGED_TARGET = 47,
    REQ_CAN_BE_TARGETED_BY_BATTLECRIES = 48, REQ_STEADY_SHOT = 49,
    REQ_MINION_OR_ENEMY_HERO = 50,
    REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 51, REQ_LEGENDARY_TARGET = 52,
    REQ_FRIENDLY_MINION_DIED_THIS_TURN = 53,
    REQ_FRIENDLY_MINION_DIED_THIS_GAME = 54, REQ_ENEMY_WEAPON_EQUIPPED = 55,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 56,
    REQ_TARGET_WITH_BATTLECRY = 57, REQ_TARGET_WITH_DEATHRATTLE = 58,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 59,
    REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 60, REQ_TARGET_EXACT_COST = 61,
    REQ_STEALTHED_TARGET = 62, REQ_MINION_SLOT_OR_MANA_CRYSTAL_SLOT = 63,
    REQ_MAX_QUESTS = 64,
    REQ_TARGET_IF_AVAILABE_AND_ELEMENTAL_PLAYED_LAST_TURN = 65,
    REQ_TARGET_NOT_VAMPIRE = 66, REQ_TARGET_NOT_DAMAGEABLE_ONLY_BY_WEAPONS = 67,
    REQ_NOT_DISABLED_HERO_POWER = 68, REQ_MUST_PLAY_OTHER_CARD_FIRST = 69,
    REQ_HAND_NOT_FULL = 70,
    REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK = 71,
    REQ_CAN_BE_TARGETED_BY_COMBOS = 72, REQ_CANNOT_PLAY_THIS = 73,
    REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 74, REQ_DRAG_TO_PLAY = 75,
    REQ_OPPONENT_PLAYED_CARDS_THIS_GAME = 77, REQ_LITERALLY_UNPLAYABLE = 78,
    REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 79,
    REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 80,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN = 81,
    REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 82)
#elif defined(ROSETTASTONE_DOXYGEN)
enum class PlayReq
{
    INVALID = -1,
    REQ_MINION_TARGET = 1,
    REQ_FRIENDLY_TARGET = 2,
    REQ_ENEMY_TARGET = 3,
    REQ_DAMAGED_TARGET = 4,
    REQ_MAX_SECRETS = 5,
    REQ_FROZEN_TARGET = 6,
    REQ_CHARGE_TARGET = 7,
    REQ_TARGET_MAX_ATTACK = 8,
    REQ_NONSELF_TARGET = 9,
    REQ_TARGET_WITH_RACE = 10,
    REQ_TARGET_TO_PLAY = 11,
    REQ_NUM_MINION_SLOTS = 12,
    REQ_WEAPON_EQUIPPED = 13,
    REQ_ENOUGH_MANA = 14,
    REQ_YOUR_TURN = 15,
    REQ_NONSTEALTH_ENEMY_TARGET = 16,
    REQ_HERO_TARGET = 17,
    REQ_SECRET_ZONE_CAP = 18,
    REQ_MINION_CAP_IF_TARGET_AVAILABLE = 19,
    REQ_MINION_CAP = 20,
    REQ_TARGET_ATTACKED_THIS_TURN = 21,
    REQ_TARGET_IF_AVAILABLE = 22,
    REQ_MINIMUM_ENEMY_MINIONS = 23,
    REQ_TARGET_FOR_COMBO = 24,
    REQ_NOT_EXHAUSTED_ACTIVATE = 25,
    REQ_UNIQUE_SECRET_OR_QUEST = 26,
    REQ_TARGET_TAUNTER = 27,
    REQ_CAN_BE_ATTACKED = 28,
    REQ_ACTION_PWR_IS_MASTER_PWR = 29,
    REQ_TARGET_MAGNET = 30,
    REQ_ATTACK_GREATER_THAN_0 = 31,
    REQ_ATTACKER_NOT_FROZEN = 32,
    REQ_HERO_OR_MINION_TARGET = 33,
    REQ_CAN_BE_TARGETED_BY_SPELLS = 34,
    REQ_SUBCARD_IS_PLAYABLE = 35,
    REQ_TARGET_FOR_NO_COMBO = 36,
    REQ_NOT_MINION_JUST_PLAYED = 37,
    REQ_NOT_EXHAUSTED_HERO_POWER = 38,
    REQ_CAN_BE_TARGETED_BY_OPPONENTS = 39,
    REQ_ATTACKER_CAN_ATTACK = 40,
    REQ_TARGET_MIN_ATTACK = 41,
    REQ_CAN_BE_TARGETED_BY_HERO_POWERS = 42,
    REQ_ENEMY_TARGET_NOT_IMMUNE = 43,
    REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 44,
    REQ_MINIMUM_TOTAL_MINIONS = 45,
    REQ_MUST_TARGET_TAUNTER = 46,
    REQ_UNDAMAGED_TARGET = 47,
    REQ_CAN_BE_TARGETED_BY_BATTLECRIES = 48,
    REQ_STEADY_SHOT = 49,
    REQ_MINION_OR_ENEMY_HERO = 50,
    REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 51,
    REQ_LEGENDARY_TARGET = 52,
    REQ_FRIENDLY_MINION_DIED_THIS_TURN = 53,
    REQ_FRIENDLY_MINION_DIED_THIS_GAME = 54,
    REQ_ENEMY_WEAPON_EQUIPPED = 55,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 56,
    REQ_TARGET_WITH_BATTLECRY = 57,
    REQ_TARGET_WITH_DEATHRATTLE = 58,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 59,
    REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 60,
    REQ_TARGET_EXACT_COST = 61,
    REQ_STEALTHED_TARGET = 62,
    REQ_MINION_SLOT_OR_MANA_CRYSTAL_SLOT = 63,
    REQ_MAX_QUESTS = 64,
    REQ_TARGET_IF_AVAILABE_AND_ELEMENTAL_PLAYED_LAST_TURN = 65,
    REQ_TARGET_NOT_VAMPIRE = 66,
    REQ_TARGET_NOT_DAMAGEABLE_ONLY_BY_WEAPONS = 67,
    REQ_NOT_DISABLED_HERO_POWER = 68,
    REQ_MUST_PLAY_OTHER_CARD_FIRST = 69,
    REQ_HAND_NOT_FULL = 70,
    REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK = 71,
    REQ_CAN_BE_TARGETED_BY_COMBOS = 72,
    REQ_CANNOT_PLAY_THIS = 73,
    REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 74,
    REQ_DRAG_TO_PLAY = 75,
    REQ_OPPONENT_PLAYED_CARDS_THIS_GAME = 77,
    REQ_LITERALLY_UNPLAYABLE = 78,
    REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 79,
    REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 80,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN = 81,
    REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 82
};
#else
namespace better_enums_data_PlayReq
{
}
class PlayReq
{
 private:
    typedef ::better_enums::optional<PlayReq> _optional;
    typedef ::better_enums::optional<std::size_t> _optional_index;

 public:
    typedef int _integral;
    enum _enumerated : int
    {
        INVALID = -1,
        REQ_MINION_TARGET = 1,
        REQ_FRIENDLY_TARGET = 2,
        REQ_ENEMY_TARGET = 3,
        REQ_DAMAGED_TARGET = 4,
        REQ_MAX_SECRETS = 5,
        REQ_FROZEN_TARGET = 6,
        REQ_CHARGE_TARGET = 7,
        REQ_TARGET_MAX_ATTACK = 8,
        REQ_NONSELF_TARGET = 9,
        REQ_TARGET_WITH_RACE = 10,
        REQ_TARGET_TO_PLAY = 11,
        REQ_NUM_MINION_SLOTS = 12,
        REQ_WEAPON_EQUIPPED = 13,
        REQ_ENOUGH_MANA = 14,
        REQ_YOUR_TURN = 15,
        REQ_NONSTEALTH_ENEMY_TARGET = 16,
        REQ_HERO_TARGET = 17,
        REQ_SECRET_ZONE_CAP = 18,
        REQ_MINION_CAP_IF_TARGET_AVAILABLE = 19,
        REQ_MINION_CAP = 20,
        REQ_TARGET_ATTACKED_THIS_TURN = 21,
        REQ_TARGET_IF_AVAILABLE = 22,
        REQ_MINIMUM_ENEMY_MINIONS = 23,
        REQ_TARGET_FOR_COMBO = 24,
        REQ_NOT_EXHAUSTED_ACTIVATE = 25,
        REQ_UNIQUE_SECRET_OR_QUEST = 26,
        REQ_TARGET_TAUNTER = 27,
        REQ_CAN_BE_ATTACKED = 28,
        REQ_ACTION_PWR_IS_MASTER_PWR = 29,
        REQ_TARGET_MAGNET = 30,
        REQ_ATTACK_GREATER_THAN_0 = 31,
        REQ_ATTACKER_NOT_FROZEN = 32,
        REQ_HERO_OR_MINION_TARGET = 33,
        REQ_CAN_BE_TARGETED_BY_SPELLS = 34,
        REQ_SUBCARD_IS_PLAYABLE = 35,
        REQ_TARGET_FOR_NO_COMBO = 36,
        REQ_NOT_MINION_JUST_PLAYED = 37,
        REQ_NOT_EXHAUSTED_HERO_POWER = 38,
        REQ_CAN_BE_TARGETED_BY_OPPONENTS = 39,
        REQ_ATTACKER_CAN_ATTACK = 40,
        REQ_TARGET_MIN_ATTACK = 41,
        REQ_CAN_BE_TARGETED_BY_HERO_POWERS = 42,
        REQ_ENEMY_TARGET_NOT_IMMUNE = 43,
        REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 44,
        REQ_MINIMUM_TOTAL_MINIONS = 45,
        REQ_MUST_TARGET_TAUNTER = 46,
        REQ_UNDAMAGED_TARGET = 47,
        REQ_CAN_BE_TARGETED_BY_BATTLECRIES = 48,
        REQ_STEADY_SHOT = 49,
        REQ_MINION_OR_ENEMY_HERO = 50,
        REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 51,
        REQ_LEGENDARY_TARGET = 52,
        REQ_FRIENDLY_MINION_DIED_THIS_TURN = 53,
        REQ_FRIENDLY_MINION_DIED_THIS_GAME = 54,
        REQ_ENEMY_WEAPON_EQUIPPED = 55,
        REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 56,
        REQ_TARGET_WITH_BATTLECRY = 57,
        REQ_TARGET_WITH_DEATHRATTLE = 58,
        REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 59,
        REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 60,
        REQ_TARGET_EXACT_COST = 61,
        REQ_STEALTHED_TARGET = 62,
        REQ_MINION_SLOT_OR_MANA_CRYSTAL_SLOT = 63,
        REQ_MAX_QUESTS = 64,
        REQ_TARGET_IF_AVAILABE_AND_ELEMENTAL_PLAYED_LAST_TURN = 65,
        REQ_TARGET_NOT_VAMPIRE = 66,
        REQ_TARGET_NOT_DAMAGEABLE_ONLY_BY_WEAPONS = 67,
        REQ_NOT_DISABLED_HERO_POWER = 68,
        REQ_MUST_PLAY_OTHER_CARD_FIRST = 69,
        REQ_HAND_NOT_FULL = 70,
        REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK = 71,
        REQ_CAN_BE_TARGETED_BY_COMBOS = 72,
        REQ_CANNOT_PLAY_THIS = 73,
        REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 74,
        REQ_DRAG_TO_PLAY = 75,
        REQ_OPPONENT_PLAYED_CARDS_THIS_GAME = 77,
        REQ_LITERALLY_UNPLAYABLE = 78,
        REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 79,
        REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 80,
        REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN = 81,
        REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 82
    };

    constexpr PlayReq(_enumerated value) : _value(value)
    {
        // Do nothing
    }
    constexpr operator _enumerated() const
    {
        return _enumerated(_value);
    }
    constexpr _integral _to_integral() const;
    constexpr static PlayReq _from_integral(_integral value);
    constexpr static PlayReq _from_integral_unchecked(_integral value);
    constexpr static _optional _from_integral_nothrow(_integral value);
    const char* _to_string() const;
    constexpr static PlayReq _from_string(const char* name);
    constexpr static _optional _from_string_nothrow(const char* name);
    constexpr static PlayReq _from_string_nocase(const char* name);
    constexpr static _optional _from_string_nocase_nothrow(const char* name);
    constexpr static bool _is_valid(_integral value);
    constexpr static bool _is_valid(const char* name);
    constexpr static bool _is_valid_nocase(const char* name);
    typedef ::better_enums::_iterable<PlayReq> _value_iterable;
    typedef ::better_enums::_iterable<const char*> _name_iterable;
    typedef _value_iterable::iterator _value_iterator;
    typedef _name_iterable::iterator _name_iterator;
    constexpr static const std::size_t _size_constant = 82;
    constexpr static std::size_t _size()
    {
        return _size_constant;
    }
    constexpr static const char* _name();
    constexpr static _value_iterable _values();
    static _name_iterable _names();
    _integral _value;

 private:
    PlayReq() : _value(0)
    {
        // Do nothing
    }

 private:
    explicit constexpr PlayReq(const _integral& value) : _value(value)
    {
        // Do nothing
    }
    static int initialize();
    constexpr static _optional_index _from_value_loop(_integral value,
                                                      std::size_t index = 0);
    constexpr static _optional_index _from_string_loop(const char* name,
                                                       std::size_t index = 0);
    constexpr static _optional_index _from_string_nocase_loop(
        const char* name, std::size_t index = 0);
    friend struct ::better_enums::_initialize_at_program_start<PlayReq>;
};

namespace better_enums_data_PlayReq
{
static ::better_enums::_initialize_at_program_start<PlayReq>
    _force_initialization;
enum _PutNamesInThisScopeAlso
{
    INVALID = -1,
    REQ_MINION_TARGET = 1,
    REQ_FRIENDLY_TARGET = 2,
    REQ_ENEMY_TARGET = 3,
    REQ_DAMAGED_TARGET = 4,
    REQ_MAX_SECRETS = 5,
    REQ_FROZEN_TARGET = 6,
    REQ_CHARGE_TARGET = 7,
    REQ_TARGET_MAX_ATTACK = 8,
    REQ_NONSELF_TARGET = 9,
    REQ_TARGET_WITH_RACE = 10,
    REQ_TARGET_TO_PLAY = 11,
    REQ_NUM_MINION_SLOTS = 12,
    REQ_WEAPON_EQUIPPED = 13,
    REQ_ENOUGH_MANA = 14,
    REQ_YOUR_TURN = 15,
    REQ_NONSTEALTH_ENEMY_TARGET = 16,
    REQ_HERO_TARGET = 17,
    REQ_SECRET_ZONE_CAP = 18,
    REQ_MINION_CAP_IF_TARGET_AVAILABLE = 19,
    REQ_MINION_CAP = 20,
    REQ_TARGET_ATTACKED_THIS_TURN = 21,
    REQ_TARGET_IF_AVAILABLE = 22,
    REQ_MINIMUM_ENEMY_MINIONS = 23,
    REQ_TARGET_FOR_COMBO = 24,
    REQ_NOT_EXHAUSTED_ACTIVATE = 25,
    REQ_UNIQUE_SECRET_OR_QUEST = 26,
    REQ_TARGET_TAUNTER = 27,
    REQ_CAN_BE_ATTACKED = 28,
    REQ_ACTION_PWR_IS_MASTER_PWR = 29,
    REQ_TARGET_MAGNET = 30,
    REQ_ATTACK_GREATER_THAN_0 = 31,
    REQ_ATTACKER_NOT_FROZEN = 32,
    REQ_HERO_OR_MINION_TARGET = 33,
    REQ_CAN_BE_TARGETED_BY_SPELLS = 34,
    REQ_SUBCARD_IS_PLAYABLE = 35,
    REQ_TARGET_FOR_NO_COMBO = 36,
    REQ_NOT_MINION_JUST_PLAYED = 37,
    REQ_NOT_EXHAUSTED_HERO_POWER = 38,
    REQ_CAN_BE_TARGETED_BY_OPPONENTS = 39,
    REQ_ATTACKER_CAN_ATTACK = 40,
    REQ_TARGET_MIN_ATTACK = 41,
    REQ_CAN_BE_TARGETED_BY_HERO_POWERS = 42,
    REQ_ENEMY_TARGET_NOT_IMMUNE = 43,
    REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 44,
    REQ_MINIMUM_TOTAL_MINIONS = 45,
    REQ_MUST_TARGET_TAUNTER = 46,
    REQ_UNDAMAGED_TARGET = 47,
    REQ_CAN_BE_TARGETED_BY_BATTLECRIES = 48,
    REQ_STEADY_SHOT = 49,
    REQ_MINION_OR_ENEMY_HERO = 50,
    REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 51,
    REQ_LEGENDARY_TARGET = 52,
    REQ_FRIENDLY_MINION_DIED_THIS_TURN = 53,
    REQ_FRIENDLY_MINION_DIED_THIS_GAME = 54,
    REQ_ENEMY_WEAPON_EQUIPPED = 55,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 56,
    REQ_TARGET_WITH_BATTLECRY = 57,
    REQ_TARGET_WITH_DEATHRATTLE = 58,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 59,
    REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 60,
    REQ_TARGET_EXACT_COST = 61,
    REQ_STEALTHED_TARGET = 62,
    REQ_MINION_SLOT_OR_MANA_CRYSTAL_SLOT = 63,
    REQ_MAX_QUESTS = 64,
    REQ_TARGET_IF_AVAILABE_AND_ELEMENTAL_PLAYED_LAST_TURN = 65,
    REQ_TARGET_NOT_VAMPIRE = 66,
    REQ_TARGET_NOT_DAMAGEABLE_ONLY_BY_WEAPONS = 67,
    REQ_NOT_DISABLED_HERO_POWER = 68,
    REQ_MUST_PLAY_OTHER_CARD_FIRST = 69,
    REQ_HAND_NOT_FULL = 70,
    REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK = 71,
    REQ_CAN_BE_TARGETED_BY_COMBOS = 72,
    REQ_CANNOT_PLAY_THIS = 73,
    REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 74,
    REQ_DRAG_TO_PLAY = 75,
    REQ_OPPONENT_PLAYED_CARDS_THIS_GAME = 77,
    REQ_LITERALLY_UNPLAYABLE = 78,
    REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 79,
    REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 80,
    REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN = 81,
    REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 82
};
constexpr const PlayReq _value_array[] = {
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::INVALID = -1),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MINION_TARGET = 1),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_FRIENDLY_TARGET = 2),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_ENEMY_TARGET = 3),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_DAMAGED_TARGET = 4),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MAX_SECRETS = 5),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_FROZEN_TARGET = 6),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_CHARGE_TARGET = 7),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_MAX_ATTACK = 8),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_NONSELF_TARGET = 9),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_WITH_RACE = 10),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_TO_PLAY = 11),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_NUM_MINION_SLOTS = 12),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_WEAPON_EQUIPPED = 13),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_ENOUGH_MANA = 14),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_YOUR_TURN = 15),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_NONSTEALTH_ENEMY_TARGET = 16),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_HERO_TARGET = 17),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_SECRET_ZONE_CAP = 18),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_MINION_CAP_IF_TARGET_AVAILABLE = 19),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MINION_CAP = 20),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_ATTACKED_THIS_TURN = 21),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_IF_AVAILABLE =
         22),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MINIMUM_ENEMY_MINIONS =
         23),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_FOR_COMBO = 24),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_NOT_EXHAUSTED_ACTIVATE =
         25),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_UNIQUE_SECRET_OR_QUEST =
         26),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_TAUNTER = 27),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_CAN_BE_ATTACKED = 28),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_ACTION_PWR_IS_MASTER_PWR = 29),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_MAGNET = 30),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_ATTACK_GREATER_THAN_0 =
         31),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_ATTACKER_NOT_FROZEN =
         32),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_HERO_OR_MINION_TARGET =
         33),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_CAN_BE_TARGETED_BY_SPELLS = 34),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_SUBCARD_IS_PLAYABLE =
         35),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_FOR_NO_COMBO =
         36),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_NOT_MINION_JUST_PLAYED =
         37),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_NOT_EXHAUSTED_HERO_POWER = 38),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_CAN_BE_TARGETED_BY_OPPONENTS = 39),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_ATTACKER_CAN_ATTACK =
         40),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_MIN_ATTACK = 41),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_CAN_BE_TARGETED_BY_HERO_POWERS = 42),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_ENEMY_TARGET_NOT_IMMUNE = 43),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 44),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MINIMUM_TOTAL_MINIONS =
         45),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MUST_TARGET_TAUNTER =
         46),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_UNDAMAGED_TARGET = 47),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_CAN_BE_TARGETED_BY_BATTLECRIES = 48),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_STEADY_SHOT = 49),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MINION_OR_ENEMY_HERO =
         50),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 51),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_LEGENDARY_TARGET = 52),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_FRIENDLY_MINION_DIED_THIS_TURN = 53),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_FRIENDLY_MINION_DIED_THIS_GAME = 54),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_ENEMY_WEAPON_EQUIPPED =
         55),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 56),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_WITH_BATTLECRY =
         57),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_WITH_DEATHRATTLE = 58),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 59),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 60),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_EXACT_COST = 61),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_STEALTHED_TARGET = 62),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_MINION_SLOT_OR_MANA_CRYSTAL_SLOT = 63),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_MAX_QUESTS = 64),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_IF_AVAILABE_AND_ELEMENTAL_PLAYED_LAST_TURN = 65),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_TARGET_NOT_VAMPIRE =
         66),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_NOT_DAMAGEABLE_ONLY_BY_WEAPONS = 67),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_NOT_DISABLED_HERO_POWER = 68),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_MUST_PLAY_OTHER_CARD_FIRST = 69),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_HAND_NOT_FULL = 70),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK = 71),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_CAN_BE_TARGETED_BY_COMBOS = 72),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_CANNOT_PLAY_THIS = 73),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 74),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_DRAG_TO_PLAY = 75),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_OPPONENT_PLAYED_CARDS_THIS_GAME = 77),
    ((::better_enums::_eat_assign<PlayReq>)PlayReq::REQ_LITERALLY_UNPLAYABLE =
         78),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 79),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 80),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN =
             81),
    ((::better_enums::_eat_assign<PlayReq>)
         PlayReq::REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 82),
};
constexpr const char* _the_raw_names[] = {
    "INVALID = -1",
    "REQ_MINION_TARGET = 1",
    "REQ_FRIENDLY_TARGET = 2",
    "REQ_ENEMY_TARGET = 3",
    "REQ_DAMAGED_TARGET = 4",
    "REQ_MAX_SECRETS = 5",
    "REQ_FROZEN_TARGET = 6",
    "REQ_CHARGE_TARGET = 7",
    "REQ_TARGET_MAX_ATTACK = 8",
    "REQ_NONSELF_TARGET = 9",
    "REQ_TARGET_WITH_RACE = 10",
    "REQ_TARGET_TO_PLAY = 11",
    "REQ_NUM_MINION_SLOTS = 12",
    "REQ_WEAPON_EQUIPPED = 13",
    "REQ_ENOUGH_MANA = 14",
    "REQ_YOUR_TURN = 15",
    "REQ_NONSTEALTH_ENEMY_TARGET = 16",
    "REQ_HERO_TARGET = 17",
    "REQ_SECRET_ZONE_CAP = 18",
    "REQ_MINION_CAP_IF_TARGET_AVAILABLE = 19",
    "REQ_MINION_CAP = 20",
    "REQ_TARGET_ATTACKED_THIS_TURN = 21",
    "REQ_TARGET_IF_AVAILABLE = 22",
    "REQ_MINIMUM_ENEMY_MINIONS = 23",
    "REQ_TARGET_FOR_COMBO = 24",
    "REQ_NOT_EXHAUSTED_ACTIVATE = 25",
    "REQ_UNIQUE_SECRET_OR_QUEST = 26",
    "REQ_TARGET_TAUNTER = 27",
    "REQ_CAN_BE_ATTACKED = 28",
    "REQ_ACTION_PWR_IS_MASTER_PWR = 29",
    "REQ_TARGET_MAGNET = 30",
    "REQ_ATTACK_GREATER_THAN_0 = 31",
    "REQ_ATTACKER_NOT_FROZEN = 32",
    "REQ_HERO_OR_MINION_TARGET = 33",
    "REQ_CAN_BE_TARGETED_BY_SPELLS = 34",
    "REQ_SUBCARD_IS_PLAYABLE = 35",
    "REQ_TARGET_FOR_NO_COMBO = 36",
    "REQ_NOT_MINION_JUST_PLAYED = 37",
    "REQ_NOT_EXHAUSTED_HERO_POWER = 38",
    "REQ_CAN_BE_TARGETED_BY_OPPONENTS = 39",
    "REQ_ATTACKER_CAN_ATTACK = 40",
    "REQ_TARGET_MIN_ATTACK = 41",
    "REQ_CAN_BE_TARGETED_BY_HERO_POWERS = 42",
    "REQ_ENEMY_TARGET_NOT_IMMUNE = 43",
    "REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 44",
    "REQ_MINIMUM_TOTAL_MINIONS = 45",
    "REQ_MUST_TARGET_TAUNTER = 46",
    "REQ_UNDAMAGED_TARGET = 47",
    "REQ_CAN_BE_TARGETED_BY_BATTLECRIES = 48",
    "REQ_STEADY_SHOT = 49",
    "REQ_MINION_OR_ENEMY_HERO = 50",
    "REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 51",
    "REQ_LEGENDARY_TARGET = 52",
    "REQ_FRIENDLY_MINION_DIED_THIS_TURN = 53",
    "REQ_FRIENDLY_MINION_DIED_THIS_GAME = 54",
    "REQ_ENEMY_WEAPON_EQUIPPED = 55",
    "REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 56",
    "REQ_TARGET_WITH_BATTLECRY = 57",
    "REQ_TARGET_WITH_DEATHRATTLE = 58",
    "REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 59",
    "REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 60",
    "REQ_TARGET_EXACT_COST = 61",
    "REQ_STEALTHED_TARGET = 62",
    "REQ_MINION_SLOT_OR_MANA_CRYSTAL_SLOT = 63",
    "REQ_MAX_QUESTS = 64",
    "REQ_TARGET_IF_AVAILABE_AND_ELEMENTAL_PLAYED_LAST_TURN = 65",
    "REQ_TARGET_NOT_VAMPIRE = 66",
    "REQ_TARGET_NOT_DAMAGEABLE_ONLY_BY_WEAPONS = 67",
    "REQ_NOT_DISABLED_HERO_POWER = 68",
    "REQ_MUST_PLAY_OTHER_CARD_FIRST = 69",
    "REQ_HAND_NOT_FULL = 70",
    "REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK = 71",
    "REQ_CAN_BE_TARGETED_BY_COMBOS = 72",
    "REQ_CANNOT_PLAY_THIS = 73",
    "REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 74",
    "REQ_DRAG_TO_PLAY = 75",
    "REQ_OPPONENT_PLAYED_CARDS_THIS_GAME = 77",
    "REQ_LITERALLY_UNPLAYABLE = 78",
    "REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 79",
    "REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 80",
    "REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN = 81",
    "REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 82"
};
constexpr const char* const* _raw_names()
{
    return _the_raw_names;
}
inline char* _name_storage()
{
    static char storage[] =
        "INVALID = -1"
        ","
        "REQ_MINION_TARGET = 1"
        ","
        "REQ_FRIENDLY_TARGET = 2"
        ","
        "REQ_ENEMY_TARGET = 3"
        ","
        "REQ_DAMAGED_TARGET = 4"
        ","
        "REQ_MAX_SECRETS = 5"
        ","
        "REQ_FROZEN_TARGET = 6"
        ","
        "REQ_CHARGE_TARGET = 7"
        ","
        "REQ_TARGET_MAX_ATTACK = 8"
        ","
        "REQ_NONSELF_TARGET = 9"
        ","
        "REQ_TARGET_WITH_RACE = 10"
        ","
        "REQ_TARGET_TO_PLAY = 11"
        ","
        "REQ_NUM_MINION_SLOTS = 12"
        ","
        "REQ_WEAPON_EQUIPPED = 13"
        ","
        "REQ_ENOUGH_MANA = 14"
        ","
        "REQ_YOUR_TURN = 15"
        ","
        "REQ_NONSTEALTH_ENEMY_TARGET = 16"
        ","
        "REQ_HERO_TARGET = 17"
        ","
        "REQ_SECRET_ZONE_CAP = 18"
        ","
        "REQ_MINION_CAP_IF_TARGET_AVAILABLE = 19"
        ","
        "REQ_MINION_CAP = 20"
        ","
        "REQ_TARGET_ATTACKED_THIS_TURN = 21"
        ","
        "REQ_TARGET_IF_AVAILABLE = 22"
        ","
        "REQ_MINIMUM_ENEMY_MINIONS = 23"
        ","
        "REQ_TARGET_FOR_COMBO = 24"
        ","
        "REQ_NOT_EXHAUSTED_ACTIVATE = 25"
        ","
        "REQ_UNIQUE_SECRET_OR_QUEST = 26"
        ","
        "REQ_TARGET_TAUNTER = 27"
        ","
        "REQ_CAN_BE_ATTACKED = 28"
        ","
        "REQ_ACTION_PWR_IS_MASTER_PWR = 29"
        ","
        "REQ_TARGET_MAGNET = 30"
        ","
        "REQ_ATTACK_GREATER_THAN_0 = 31"
        ","
        "REQ_ATTACKER_NOT_FROZEN = 32"
        ","
        "REQ_HERO_OR_MINION_TARGET = 33"
        ","
        "REQ_CAN_BE_TARGETED_BY_SPELLS = 34"
        ","
        "REQ_SUBCARD_IS_PLAYABLE = 35"
        ","
        "REQ_TARGET_FOR_NO_COMBO = 36"
        ","
        "REQ_NOT_MINION_JUST_PLAYED = 37"
        ","
        "REQ_NOT_EXHAUSTED_HERO_POWER = 38"
        ","
        "REQ_CAN_BE_TARGETED_BY_OPPONENTS = 39"
        ","
        "REQ_ATTACKER_CAN_ATTACK = 40"
        ","
        "REQ_TARGET_MIN_ATTACK = 41"
        ","
        "REQ_CAN_BE_TARGETED_BY_HERO_POWERS = 42"
        ","
        "REQ_ENEMY_TARGET_NOT_IMMUNE = 43"
        ","
        "REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 44"
        ","
        "REQ_MINIMUM_TOTAL_MINIONS = 45"
        ","
        "REQ_MUST_TARGET_TAUNTER = 46"
        ","
        "REQ_UNDAMAGED_TARGET = 47"
        ","
        "REQ_CAN_BE_TARGETED_BY_BATTLECRIES = 48"
        ","
        "REQ_STEADY_SHOT = 49"
        ","
        "REQ_MINION_OR_ENEMY_HERO = 50"
        ","
        "REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 51"
        ","
        "REQ_LEGENDARY_TARGET = 52"
        ","
        "REQ_FRIENDLY_MINION_DIED_THIS_TURN = 53"
        ","
        "REQ_FRIENDLY_MINION_DIED_THIS_GAME = 54"
        ","
        "REQ_ENEMY_WEAPON_EQUIPPED = 55"
        ","
        "REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 56"
        ","
        "REQ_TARGET_WITH_BATTLECRY = 57"
        ","
        "REQ_TARGET_WITH_DEATHRATTLE = 58"
        ","
        "REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 59"
        ","
        "REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 60"
        ","
        "REQ_TARGET_EXACT_COST = 61"
        ","
        "REQ_STEALTHED_TARGET = 62"
        ","
        "REQ_MINION_SLOT_OR_MANA_CRYSTAL_SLOT = 63"
        ","
        "REQ_MAX_QUESTS = 64"
        ","
        "REQ_TARGET_IF_AVAILABE_AND_ELEMENTAL_PLAYED_LAST_TURN = 65"
        ","
        "REQ_TARGET_NOT_VAMPIRE = 66"
        ","
        "REQ_TARGET_NOT_DAMAGEABLE_ONLY_BY_WEAPONS = 67"
        ","
        "REQ_NOT_DISABLED_HERO_POWER = 68"
        ","
        "REQ_MUST_PLAY_OTHER_CARD_FIRST = 69"
        ","
        "REQ_HAND_NOT_FULL = 70"
        ","
        "REQ_TARGET_IF_AVAILABLE_AND_NO_3_COST_CARD_IN_DECK = 71"
        ","
        "REQ_CAN_BE_TARGETED_BY_COMBOS = 72"
        ","
        "REQ_CANNOT_PLAY_THIS = 73"
        ","
        "REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 74"
        ","
        "REQ_DRAG_TO_PLAY = 75"
        ","
        "REQ_OPPONENT_PLAYED_CARDS_THIS_GAME = 77"
        ","
        "REQ_LITERALLY_UNPLAYABLE = 78"
        ","
        "REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 79"
        ","
        "REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 80"
        ","
        "REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN = 81"
        ","
        "REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 82"
        ",";
    return storage;
}
inline const char** _name_array()
{
    static const char* value[PlayReq::_size_constant];
    return value;
}
inline bool& _initialized()
{
    static bool value = false;
    return value;
}
}  // namespace better_enums_data_PlayReq

constexpr inline const PlayReq operator+(PlayReq::_enumerated enumerated)
{
    return static_cast<PlayReq>(enumerated);
}
constexpr inline PlayReq::_optional_index PlayReq::_from_value_loop(
    PlayReq::_integral value, std::size_t index)
{
    return index == _size()
               ? _optional_index()
               : better_enums_data_PlayReq::_value_array[index]._value == value
                     ? _optional_index(index)
                     : _from_value_loop(value, index + 1);
}
constexpr inline PlayReq::_optional_index PlayReq::_from_string_loop(
    const char* name, std::size_t index)
{
    return index == _size()
               ? _optional_index()
               : ::better_enums::_names_match(
                     better_enums_data_PlayReq::_raw_names()[index], name)
                     ? _optional_index(index)
                     : _from_string_loop(name, index + 1);
}
constexpr inline PlayReq::_optional_index PlayReq::_from_string_nocase_loop(
    const char* name, std::size_t index)
{
    return index == _size()
               ? _optional_index()
               : ::better_enums::_names_match_nocase(
                     better_enums_data_PlayReq::_raw_names()[index], name)
                     ? _optional_index(index)
                     : _from_string_nocase_loop(name, index + 1);
}
constexpr inline PlayReq::_integral PlayReq::_to_integral() const
{
    return _integral(_value);
}
constexpr inline PlayReq PlayReq::_from_integral_unchecked(_integral value)
{
    return static_cast<_enumerated>(value);
}
constexpr inline PlayReq::_optional PlayReq::_from_integral_nothrow(
    _integral value)
{
    return ::better_enums::_map_index<PlayReq>(
        better_enums_data_PlayReq::_value_array, _from_value_loop(value));
}
constexpr inline PlayReq PlayReq::_from_integral(_integral value)
{
    return ::better_enums::_or_throw(_from_integral_nothrow(value),
                                     "PlayReq"
                                     "::_from_integral: invalid argument");
}
inline const char* PlayReq::_to_string() const
{
    return ::better_enums::_or_null(::better_enums::_map_index<const char*>(
        better_enums_data_PlayReq::_name_array(),
        _from_value_loop(::better_enums::continue_with(initialize(), _value))));
}
constexpr inline PlayReq::_optional PlayReq::_from_string_nothrow(
    const char* name)
{
    return ::better_enums::_map_index<PlayReq>(
        better_enums_data_PlayReq::_value_array, _from_string_loop(name));
}
constexpr inline PlayReq PlayReq::_from_string(const char* name)
{
    return ::better_enums::_or_throw(_from_string_nothrow(name),
                                     "PlayReq"
                                     "::_from_string: invalid argument");
}
constexpr inline PlayReq::_optional PlayReq::_from_string_nocase_nothrow(
    const char* name)
{
    return ::better_enums::_map_index<PlayReq>(
        better_enums_data_PlayReq::_value_array,
        _from_string_nocase_loop(name));
}
constexpr inline PlayReq PlayReq::_from_string_nocase(const char* name)
{
    return ::better_enums::_or_throw(_from_string_nocase_nothrow(name),
                                     "PlayReq"
                                     "::_from_string_nocase: invalid argument");
}
constexpr inline bool PlayReq::_is_valid(_integral value)
{
    return _from_value_loop(value);
}
constexpr inline bool PlayReq::_is_valid(const char* name)
{
    return _from_string_loop(name);
}
constexpr inline bool PlayReq::_is_valid_nocase(const char* name)
{
    return _from_string_nocase_loop(name);
}
constexpr inline const char* PlayReq::_name()
{
    return "PlayReq";
}
constexpr inline PlayReq::_value_iterable PlayReq::_values()
{
    return _value_iterable(better_enums_data_PlayReq::_value_array, _size());
}
inline PlayReq::_name_iterable PlayReq::_names()
{
    return _name_iterable(better_enums_data_PlayReq::_name_array(),
                          ::better_enums::continue_with(initialize(), _size()));
}
inline int PlayReq::initialize()
{
    if (better_enums_data_PlayReq::_initialized())
        return 0;
    ::better_enums::_trim_names(better_enums_data_PlayReq::_raw_names(),
                                better_enums_data_PlayReq::_name_array(),
                                better_enums_data_PlayReq::_name_storage(),
                                _size());
    better_enums_data_PlayReq::_initialized() = true;
    return 0;
}
constexpr inline bool operator==(const PlayReq& a, const PlayReq& b)
{
    return a._to_integral() == b._to_integral();
}
constexpr inline bool operator!=(const PlayReq& a, const PlayReq& b)
{
    return a._to_integral() != b._to_integral();
}
constexpr inline bool operator<(const PlayReq& a, const PlayReq& b)
{
    return a._to_integral() < b._to_integral();
}
constexpr inline bool operator<=(const PlayReq& a, const PlayReq& b)
{
    return a._to_integral() <= b._to_integral();
}
constexpr inline bool operator>(const PlayReq& a, const PlayReq& b)
{
    return a._to_integral() > b._to_integral();
}
constexpr inline bool operator>=(const PlayReq& a, const PlayReq& b)
{
    return a._to_integral() >= b._to_integral();
}
template <typename Char, typename Traits>
std::basic_ostream<Char, Traits>& operator<<(
    std::basic_ostream<Char, Traits>& stream, const PlayReq& value)
{
    return stream << value._to_string();
}
template <typename Char, typename Traits>
std::basic_istream<Char, Traits>& operator>>(
    std::basic_istream<Char, Traits>& stream, PlayReq& value)
{
    std::basic_string<Char, Traits> buffer;
    stream >> buffer;
    ::better_enums::optional<PlayReq> converted =
        PlayReq::_from_string_nothrow(buffer.c_str());
    if (converted)
        value = *converted;
    else
        stream.setstate(std::basic_istream<Char, Traits>::failbit);
    return stream;
}
#endif

#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(PlayState, int, INVALID = 0, PLAYING = 1, WINNING = 2, LOSING = 3,
            WON = 4, LOST = 5, TIED = 6, DISCONNECTED = 7, CONCEDED = 8)

BETTER_ENUM(PowerType, int, FULL_ENTITY = 1, SHOW_ENTITY = 2, HIDE_ENTITY = 3,
            TAG_CHANGE = 4, BLOCK_START = 5, ACTION_START = 5, BLOCK_END = 6,
            ACTION_END = 6, CREATE_GAME = 7, META_DATA = 8, CHANGE_ENTITY = 9,
            RESET_GAME = 10)
#endif

//! \brief An enumerator for identifying the race of the card.
#ifndef ROSETTASTONE_DOXYGEN
BETTER_ENUM(Race, int, INVALID = 0, BLOODELF = 1, DRAENEI = 2, DWARF = 3,
            GNOME = 4, GOBLIN = 5, HUMAN = 6, NIGHTELF = 7, ORC = 8, TAUREN = 9,
            TROLL = 10, UNDEAD = 11, WORGEN = 12, GOBLIN2 = 13, MURLOC = 14,
            DEMON = 15, SCOURGE = 16, MECHANICAL = 17, ELEMENTAL = 18,
            OGRE = 19, BEAST = 20, PET = 20, TOTEM = 21, NERUBIAN = 22,
            PIRATE = 23, DRAGON = 24, BLANK = 25, ALL = 26, EGG = 38)
#else
enum class Race
{
    INVALID = 0,
    BLOODELF = 1,
    DRAENEI = 2,
    DWARF = 3,
    GNOME = 4,
    GOBLIN = 5,
    HUMAN = 6,
    NIGHTELF = 7,
    ORC = 8,
    TAUREN = 9,
    TROLL = 10,
    UNDEAD = 11,
    WORGEN = 12,
    GOBLIN2 = 13,
    MURLOC = 14,
    DEMON = 15,
    SCOURGE = 16,
    MECHANICAL = 17,
    ELEMENTAL = 18,
    OGRE = 19,
    BEAST = 20,
    PET = 20,
    TOTEM = 21,
    NERUBIAN = 22,
    PIRATE = 23,
    DRAGON = 24,
    BLANK = 25,
    ALL = 26,
    EGG = 38
};
#endif

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
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_ENUMS_HPP
