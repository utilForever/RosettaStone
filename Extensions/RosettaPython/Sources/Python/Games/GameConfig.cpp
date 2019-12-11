// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Games/GameConfig.hpp>
#include <Rosetta/Games/GameConfig.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;

void AddGameConfig(pybind11::module& m)
{
    pybind11::class_<GameConfig>(
        m, "GameConfig",
        R"pbdoc(This struct holds all configuration values to create a new Game instance.)pbdoc")
        .def_readwrite("format_type", &GameConfig::formatType)
        .def_readwrite("start_player", &GameConfig::startPlayer)
        .def_readwrite("player1_class", &GameConfig::player1Class)
        .def_readwrite("player2_class", &GameConfig::player2Class)
        .def_readwrite("player1_deck", &GameConfig::player1Deck)
        .def_readwrite("player2_deck", &GameConfig::player2Deck)
        .def_readwrite("fill_card_ids", &GameConfig::fillCardIDs)
        .def_readwrite("do_fill_decks", &GameConfig::doFillDecks)
        .def_readwrite("do_shuffle", &GameConfig::doShuffle)
        .def_readwrite("skip_mulligan", &GameConfig::skipMulligan)
        .def_readwrite("auto_run", &GameConfig::autoRun);
}
