// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Actions/ActionParams.hpp>
#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Actions/ActionValidGetter.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddActionParams(pybind11::module& m)
{
    pybind11::class_<ActionParams>(
        m, "ActionParams",
        R"pbdoc(This class contains several parameter methods for the action such as choose main operation/hand card and get specified target/attacker/number and so on.)pbdoc")
        .def(
            "initialize",
            (void (ActionParams::*)(const Game&)) & ActionParams::Initialize,
            R"pbdoc(Initializes action params by running ActionValidChecker::Check method.

            Parameters
            ----------
            - game : The game context)pbdoc",
            pybind11::arg("game"))
        .def(
            "initialize",
            (void (ActionParams::*)(ActionValidGetter&)) &
                ActionParams::Initialize,
            R"pbdoc(Initializes action params by running ActionValidChecker::Check method.

            Parameters
            ----------
            - getter : The action valid getter.)pbdoc",
            pybind11::arg("getter"))
        .def("get_checker", &ActionParams::GetChecker,
             R"pbdoc(Returns the action valid checker.

             The action valid checker.)pbdoc")
        .def("choose_main_op", &ActionParams::ChooseMainOp,
             R"pbdoc(Returns the main operation using the action valid checker.

             The chosen main operation.)pbdoc")
        .def("get_minion_put_location", &ActionParams::GetMinionPutLocation,
             R"pbdoc(Returns the location of minion to put.

             The chosen location of minion.

             Parameters
             ----------
             - minions : The number of minions in field zone.)pbdoc",
             pybind11::arg("minions"))
        .def("get_specified_target", &ActionParams::GetSpecifiedTarget,
             R"pbdoc(Returns the specified target.

             The chosen specified target.

             Parameters
             ----------
             - targets : A list of targets that can specify.)pbdoc",
             pybind11::arg("targets"))
        .def("choose_one", &ActionParams::ChooseOne,
             R"pbdoc(Returns a card from a list of choice cards.

             A chosen card from a list of choice cards.

             Parameters
             ----------
             - cards : A list of choice cards.)pbdoc",
             pybind11::arg("cards"))
        .def("choose_hand_card", &ActionParams::ChooseHandCard,
             R"pbdoc(Returns a card in hand zone that is playable.

             A chosen card in hand zone that is playable.)pbdoc")
        .def("get_attacker", &ActionParams::GetAttacker,
             R"pbdoc(Returns a minion card in field zone that can attack.

             A chosen minion card in field zone that can attack.)pbdoc")
        .def("get_number",
             (std::size_t(ActionParams::*)(ActionType, ActionChoices&)) &
                 ActionParams::GetNumber,
             R"pbdoc(Returns the number using actionType and choices.

             The chosen number using action type and action choices.
             
             Parameters
             ----------
             - action_type : The action type.
             - choices : The action choices.)pbdoc",
             pybind11::arg("action_type"), pybind11::arg("choices"));
}
