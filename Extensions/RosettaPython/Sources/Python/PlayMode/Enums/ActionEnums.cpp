// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Enums/ActionEnums.hpp>
#include <Rosetta/Common/Enums/ActionEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddActionEnums(pybind11::module& m)
{
    pybind11::enum_<MainOpType>(
        m, "MainOpType",
        R"pbdoc(An enumerator for identifying main operation type.)pbdoc")
        .value("INVALID", MainOpType::INVALID)
        .value("PLAY_CARD", MainOpType::PLAY_CARD)
        .value("ATTACK", MainOpType::ATTACK)
        .value("USE_HERO_POWER", MainOpType::USE_HERO_POWER)
        .value("END_TURN", MainOpType::END_TURN);

    pybind11::enum_<ActionType>(
        m, "ActionType",
        R"pbdoc(An enumerator for identifying action type.)pbdoc")
        .value("INVALID", ActionType::INVALID)
        .value("RANDOM", ActionType::RANDOM)
        .value("MAIN_ACTION", ActionType::MAIN_ACTION)
        .value("CHOOSE_HAND_CARD", ActionType::CHOOSE_HAND_CARD)
        .value("CHOOSE_ATTACKER", ActionType::CHOOSE_ATTACKER)
        .value("CHOOSE_MINION_PUT_LOCATION",
               ActionType::CHOOSE_MINION_PUT_LOCATION)
        .value("CHOOSE_TARGET", ActionType::CHOOSE_TARGET)
        .value("CHOOSE_ONE", ActionType::CHOOSE_ONE);

    m.def("GetMainOpString", GetMainOpString,
          R"pbdoc(Returns the string of the main operation type.

          Parameters
          ----------
          - op : The string of the main operation type.)pbdoc",
          pybind11::arg("op"));
}
