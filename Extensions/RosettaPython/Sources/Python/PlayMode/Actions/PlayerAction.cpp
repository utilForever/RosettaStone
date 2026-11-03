// Copyright (c) 2026 Chris Ohk

#include <Python/PlayMode/Actions/PlayerAction.hpp>
#include <Rosetta/PlayMode/Actions/PlayerAction.hpp>

#include <functional>

using namespace RosettaStone::PlayMode;

void AddPlayerAction(const pybind11::module& m)
{
    using enum PlayerActionType;

    pybind11::enum_<PlayerActionType>(m, "PlayerActionType")
        .value("END_TURN", END_TURN)
        .value("PLAY_CARD", PLAY_CARD)
        .value("ATTACK", ATTACK)
        .value("HERO_POWER", HERO_POWER)
        .value("CHOOSE", CHOOSE);

    pybind11::class_<PlayerAction>(
        m, "PlayerAction",
        R"pbdoc(A semantic player decision with game-local entity IDs.
        Values compare lexicographically by type, source_id, target_id,
        field_pos, choose_one, and choice_id. Game execution and action
        enumeration are currently available through the C++ API.)pbdoc")
        .def(pybind11::init<PlayerActionType, int, int, int, int, int>(),
             pybind11::arg("type") = END_TURN, pybind11::arg("source_id") = -1,
             pybind11::arg("target_id") = -1, pybind11::arg("field_pos") = -1,
             pybind11::arg("choose_one") = 0, pybind11::arg("choice_id") = -1)
        .def_readwrite("type", &PlayerAction::type)
        .def_readwrite("source_id", &PlayerAction::sourceID)
        .def_readwrite("target_id", &PlayerAction::targetID)
        .def_readwrite("field_pos", &PlayerAction::fieldPos)
        .def_readwrite("choose_one", &PlayerAction::chooseOne)
        .def_readwrite("choice_id", &PlayerAction::choiceID)
        .def("__eq__", std::equal_to<PlayerAction>{}, pybind11::is_operator())
        .def("__ne__", std::not_equal_to<PlayerAction>{},
             pybind11::is_operator())
        .def("__lt__", std::less<PlayerAction>{}, pybind11::is_operator())
        .def("__le__", std::less_equal<PlayerAction>{}, pybind11::is_operator())
        .def("__gt__", std::greater<PlayerAction>{}, pybind11::is_operator())
        .def("__ge__", std::greater_equal<PlayerAction>{},
             pybind11::is_operator());
}
