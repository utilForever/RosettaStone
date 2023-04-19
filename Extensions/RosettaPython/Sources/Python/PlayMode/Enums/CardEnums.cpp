// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/CardEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddCardEnums(pybind11::module& m)
{
    pybind11::enum_<CardClass>(
        m, "CardClass",
        R"pbdoc(An enumerator for identifying the class of the card.)pbdoc")
#define X(a) .value(#a, CardClass::a)
#include "Rosetta/Common/Enums/CardClass.def"
#undef X
        ;

    pybind11::enum_<CardSet>(
        m, "CardSet",
        R"pbdoc(An enumerator for identifying the set of the card.)pbdoc")
#define X(a) .value(#a, CardSet::a)
#include "Rosetta/Common/Enums/CardSet.def"
#undef X
        ;

    pybind11::enum_<CardType>(
        m, "CardType",
        R"pbdoc(An enumerator for identifying the type of the card.)pbdoc")
#define X(a) .value(#a, CardType::a)
#include "Rosetta/Common/Enums/CardType.def"
#undef X
        ;

    pybind11::enum_<Faction>(
        m, "Faction",
        R"pbdoc(An enumerator for identifying the faction of the card.)pbdoc")
#define X(a) .value(#a, Faction::a)
#include "Rosetta/Common/Enums/Faction.def"
#undef X
        ;

    pybind11::enum_<GameTag>(
        m, "GameTag",
        R"pbdoc(An enumerator for identifying the game tag of the card.)pbdoc")
#define X(a) .value(#a, GameTag::a)
#include "Rosetta/Common/Enums/GameTag.def"
#undef X
        ;

    pybind11::enum_<PlayReq>(
        m, "PlayReq",
        R"pbdoc(An enumerator for identifying the play requirement of the card.)pbdoc")
#define X(a) .value(#a, PlayReq::a)
#include "Rosetta/Common/Enums/PlayReq.def"
#undef X
        ;

    pybind11::enum_<Race>(
        m, "Race",
        R"pbdoc(An enumerator for identifying the race of the card.)pbdoc")
#define X(a) .value(#a, Race::a)
#include "Rosetta/Common/Enums/Race.def"
#undef X
        ;

    pybind11::enum_<Rarity>(
        m, "Rarity",
        R"pbdoc(An enumerator for identifying the rarity of the card.)pbdoc")
#define X(a) .value(#a, Rarity::a)
#include "Rosetta/Common/Enums/Rarity.def"
#undef X
        ;

    pybind11::enum_<Locale>(
        m, "Locale",
        R"pbdoc(An enumerator for identifying the locale of the card.)pbdoc")
        .value("UNKNOWN", Locale::UNKNOWN)
        .value("enUS", Locale::enUS)
        .value("enGB", Locale::enGB)
        .value("frFR", Locale::frFR)
        .value("deDE", Locale::deDE)
        .value("koKR", Locale::koKR)
        .value("esES", Locale::esES)
        .value("esMX", Locale::esMX)
        .value("ruRU", Locale::ruRU)
        .value("zhTW", Locale::zhTW)
        .value("zhCN", Locale::zhCN)
        .value("itIT", Locale::itIT)
        .value("ptBR", Locale::ptBR)
        .value("plPL", Locale::plPL)
        .value("ptPT", Locale::ptPT)
        .value("jaJP", Locale::jaJP)
        .value("thTH", Locale::thTH);

    pybind11::enum_<Mulligan>(
        m, "Mulligan",
        R"pbdoc(An enumerator for identifying the mulligan state.)pbdoc")
        .value("INVALID", Mulligan::INVALID)
        .value("INPUT", Mulligan::INPUT)
        .value("DEALING", Mulligan::DEALING)
        .value("WAITING", Mulligan::WAITING)
        .value("DONE", Mulligan::DONE);

    pybind11::enum_<ChoiceType>(
        m, "ChoiceType",
        R"pbdoc(An enumerator for identifying the choice type of the card.)pbdoc")
        .value("INVALID", ChoiceType::INVALID)
        .value("MULLIGAN", ChoiceType::MULLIGAN)
        .value("GENERAL", ChoiceType::GENERAL);

    pybind11::enum_<FormatType>(
        m, "FormatType",
        R"pbdoc(An enumerator for identifying the format type of the card.)pbdoc")
        .value("UNKNOWN", FormatType::UNKNOWN)
        .value("WILD", FormatType::WILD)
        .value("STANDARD", FormatType::STANDARD);

    pybind11::enum_<PlayState>(
        m, "PlayState",
        R"pbdoc(An enumerator for identifying the play state.)pbdoc")
        .value("INVALID", PlayState::INVALID)
        .value("PLAYING", PlayState::PLAYING)
        .value("WINNING", PlayState::WINNING)
        .value("LOSING", PlayState::LOSING)
        .value("WON", PlayState::WON)
        .value("LOST", PlayState::LOST)
        .value("TIED", PlayState::TIED)
        .value("DISCONNECTED", PlayState::DISCONNECTED)
        .value("CONCEDED", PlayState::CONCEDED);

    pybind11::enum_<State>(
        m, "State",
        R"pbdoc(An enumerator for indicating the state of the card.)pbdoc")
        .value("INVALID", State::INVALID)
        .value("LOADING", State::LOADING)
        .value("RUNNING", State::RUNNING)
        .value("COMPLETE", State::COMPLETE);

    pybind11::enum_<Step>(
        m, "Step", R"pbdoc(An enumerator for indicating the game step.)pbdoc")
        .value("INVALID", Step::INVALID)
        .value("BEGIN_FIRST", Step::BEGIN_FIRST)
        .value("BEGIN_SHUFFLE", Step::BEGIN_SHUFFLE)
        .value("BEGIN_DRAW", Step::BEGIN_DRAW)
        .value("BEGIN_MULLIGAN", Step::BEGIN_MULLIGAN)
        .value("MAIN_BEGIN", Step::MAIN_BEGIN)
        .value("MAIN_READY", Step::MAIN_READY)
        .value("MAIN_RESOURCE", Step::MAIN_RESOURCE)
        .value("MAIN_DRAW", Step::MAIN_DRAW)
        .value("MAIN_START", Step::MAIN_START)
        .value("MAIN_ACTION", Step::MAIN_ACTION)
        .value("MAIN_COMBAT", Step::MAIN_COMBAT)
        .value("MAIN_END", Step::MAIN_END)
        .value("MAIN_NEXT", Step::MAIN_NEXT)
        .value("FINAL_WRAPUP", Step::FINAL_WRAPUP)
        .value("FINAL_GAMEOVER", Step::FINAL_GAMEOVER)
        .value("MAIN_CLEANUP", Step::MAIN_CLEANUP)
        .value("MAIN_START_TRIGGERS", Step::MAIN_START_TRIGGERS);

    pybind11::enum_<ZoneType>(
        m, "ZoneType",
        R"pbdoc(An enumerator for indicating the type of zone.)pbdoc")
        .value("INVALID", ZoneType::INVALID)
        .value("PLAY", ZoneType::PLAY)
        .value("DECK", ZoneType::DECK)
        .value("HAND", ZoneType::HAND)
        .value("GRAVEYARD", ZoneType::GRAVEYARD)
        .value("REMOVEDFROMGAME", ZoneType::REMOVEDFROMGAME)
        .value("SETASIDE", ZoneType::SETASIDE)
        .value("SECRET", ZoneType::SECRET);
}