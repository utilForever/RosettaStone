// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CARD_ENUMS_HPP
#define ROSETTASTONE_CARD_ENUMS_HPP

#include <string>
#include <string_view>

namespace RosettaStone
{
//! \brief An enumerator for identifying the class of the card.
enum class CardClass
{
#define X(a) a,
#include "Rosetta/Common/Enums/CardClass.def"
#undef X
};

const std::string CARD_CLASS_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/CardClass.def"
#undef X
};

//! \brief An enumerator for identifying the multi class group of the card.
enum class MultiClassGroup
{
#define X(a) a,
#include "Rosetta/Common/Enums/MultiClassGroup.def"
#undef X
};

const std::string MULTI_CLASS_GROUP_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/MultiClassGroup.def"
#undef X
};

//! \brief An enumerator for identifying the set of the card.
enum class CardSet
{
#define X(a) a,
#include "Rosetta/Common/Enums/CardSet.def"
#undef X
};

const std::string CARD_SET_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/CardSet.def"
#undef X
};

//! \brief An enumerator for identifying the type of the card.
enum class CardType
{
#define X(a) a,
#include "Rosetta/Common/Enums/CardType.def"
#undef X
};

const std::string CARD_TYPE_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/CardType.def"
#undef X
};

//! \brief An enumerator for identifying the faction of the card.
enum class Faction
{
#define X(a) a,
#include "Rosetta/Common/Enums/Faction.def"
#undef X
};

const std::string FACTION_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/Faction.def"
#undef X
};

//! \brief An enumerator for identifying the game tag of the card.
enum class GameTag
{
#define X(a) a,
#include "Rosetta/Common/Enums/GameTag.def"
#include "Rosetta/Common/Enums/GameTagCustom.def"
#undef X
};

const std::string GAME_TAG_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/GameTag.def"
#include "Rosetta/Common/Enums/GameTagCustom.def"
#undef X
};

//! \brief An enumerator for identifying the play requirement of the card.
enum class PlayReq
{
#define X(a) a,
#include "Rosetta/Common/Enums/PlayReq.def"
#include "Rosetta/Common/Enums/PlayReqCustom.def"
#undef X
};

const std::string PLAY_REQ_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/PlayReq.def"
#include "Rosetta/Common/Enums/PlayReqCustom.def"
#undef X
};

//! \brief An enumerator for identifying the race of the card.
enum class Race
{
#define X(a) a,
#include "Rosetta/Common/Enums/Race.def"
#undef X
};

const std::string RACE_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/Race.def"
#undef X
};

//! \brief An enumerator for identifying the rarity of the card.
enum class Rarity
{
#define X(a) a,
#include "Rosetta/Common/Enums/Rarity.def"
#undef X
};

const std::string RARITY_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/Rarity.def"
#undef X
};

//! \brief An enumerator for identifying the spell school of the card.
enum class SpellSchool
{
#define X(a) a,
#include "Rosetta/Common/Enums/SpellSchool.def"
#undef X
};

const std::string SPELL_SCHOOL_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/SpellSchool.def"
#undef X
};

//! \brief An enumerator for identifying the locale of the card.
enum class Locale
{
    UNKNOWN,
    enUS,
    enGB,
    frFR,
    deDE,
    koKR,
    esES,
    esMX,
    ruRU,
    zhTW,
    zhCN,
    itIT,
    ptBR,
    plPL,
    ptPT,
    jaJP,
    thTH
};

//! \brief An enumerator for identifying the mulligan state.
enum class Mulligan
{
    INVALID,
    INPUT,
    DEALING,
    WAITING,
    DONE
};

//! \brief An enumerator for identifying the choice type of the card.
enum class ChoiceType
{
    INVALID,
    MULLIGAN,
    GENERAL,
    TARGET
};

//! \brief An enumerator for identifying the format type of the card.
enum class FormatType
{
    UNKNOWN,
    WILD,
    STANDARD,
    CLASSIC
};

//! \brief An enumerator for identifying the play state.
enum class PlayState
{
    INVALID,
    PLAYING,
    WINNING,
    LOSING,
    WON,
    LOST,
    TIED,
    DISCONNECTED,
    CONCEDED
};

//! \brief An enumerator for indicating the state of the card.
enum class State
{
    INVALID,
    LOADING,
    RUNNING,
    COMPLETE
};

//! \brief An enumerator for indicating the game step.
enum class Step
{
    INVALID,
    BEGIN_FIRST,
    BEGIN_SHUFFLE,
    BEGIN_DRAW,
    BEGIN_MULLIGAN,
    MAIN_BEGIN,
    MAIN_READY,
    MAIN_RESOURCE,
    MAIN_DRAW,
    MAIN_START,
    MAIN_ACTION,
    MAIN_COMBAT,
    MAIN_END,
    MAIN_NEXT,
    FINAL_WRAPUP,
    FINAL_GAMEOVER,
    MAIN_CLEANUP,
    MAIN_START_TRIGGERS
};

//! \brief An enumerator for indicating the type of zone.
enum class ZoneType
{
    INVALID,
    PLAY,
    DECK,
    HAND,
    GRAVEYARD,
    REMOVEDFROMGAME,
    SETASIDE,
    SECRET
};

template <class T>
T StrToEnum(const std::string_view&);
template <class T>
std::string_view EnumToStr(T);

#define STR2ENUM(TYPE, ARRAY)                                                \
    template <>                                                              \
    inline TYPE StrToEnum<TYPE>(const std::string_view& str)                 \
    {                                                                        \
        for (std::size_t i = 0; i < (sizeof(ARRAY) / sizeof(ARRAY[0])); ++i) \
        {                                                                    \
            if (ARRAY[i] == str)                                             \
            {                                                                \
                return TYPE(i);                                              \
            }                                                                \
        }                                                                    \
                                                                             \
        return TYPE(0);                                                      \
    }

#define ENUM2STR(TYPE, ARRAY)                       \
    template <>                                     \
    inline std::string_view EnumToStr<TYPE>(TYPE v) \
    {                                               \
        return ARRAY[static_cast<int>(v)];          \
    }

#define ENUM_AND_STR(TYPE, ARRAY) \
    STR2ENUM(TYPE, ARRAY)         \
    ENUM2STR(TYPE, ARRAY)

ENUM_AND_STR(CardClass, CARD_CLASS_STR)
ENUM_AND_STR(MultiClassGroup, MULTI_CLASS_GROUP_STR)
ENUM_AND_STR(CardSet, CARD_SET_STR)
ENUM_AND_STR(CardType, CARD_TYPE_STR)
ENUM_AND_STR(Faction, FACTION_STR)
ENUM_AND_STR(GameTag, GAME_TAG_STR)
ENUM_AND_STR(PlayReq, PLAY_REQ_STR)
ENUM_AND_STR(Race, RACE_STR)
ENUM_AND_STR(Rarity, RARITY_STR)
ENUM_AND_STR(SpellSchool, SPELL_SCHOOL_STR)
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_ENUMS_HPP