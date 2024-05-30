// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Utils/Constants.hpp>
#include <Rosetta/Common/Constants.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddConstants(pybind11::module& m)
{
    m.attr("VERSION") = pybind11::float_(VERSION);
    m.attr("DECK_CODE_VERSION") = pybind11::int_(DECK_CODE_VERSION);

    m.attr("INVALID_CARD_ID") = pybind11::str(INVALID_CARD_ID);

    m.attr("NUM_PLAY_MODE_CARDS") = pybind11::int_(NUM_PLAY_MODE_CARDS);
    m.attr("NUM_PLAYER_CLASS") = pybind11::int_(NUM_PLAYER_CLASS);
    m.attr("START_DECK_SIZE") = pybind11::int_(START_DECK_SIZE);
    m.attr("MAX_DECK_SIZE") = pybind11::int_(MAX_DECK_SIZE);
    m.attr("MAX_FIELD_SIZE") = pybind11::int_(MAX_FIELD_SIZE);
    m.attr("NUM_DRAW_CARDS_AT_START_FIRST") =
        pybind11::int_(NUM_DRAW_CARDS_AT_START_FIRST);
    m.attr("NUM_DRAW_CARDS_AT_START_SECOND") =
        pybind11::int_(NUM_DRAW_CARDS_AT_START_SECOND);

    m.attr("MANA_LOWER_LIMIT") = pybind11::int_(MANA_LOWER_LIMIT);
    m.attr("MANA_UPPER_LIMIT") = pybind11::int_(MANA_UPPER_LIMIT);

    m.attr("MAX_HAND_SIZE") = pybind11::int_(MAX_HAND_SIZE);
    m.attr("MAX_SECERT_SIZE") = pybind11::int_(MAX_SECERT_SIZE);
    m.attr("GAME_MAIN_MENU_SIZE") = pybind11::int_(GAME_MAIN_MENU_SIZE);
}
