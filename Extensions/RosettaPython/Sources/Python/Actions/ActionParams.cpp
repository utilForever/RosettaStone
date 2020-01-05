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
    pybind11::class_<ActionParams>(m, "ActionParams")
        .def("initialize",
             (void (ActionParams::*)(const Game&)) & ActionParams::Initialize)
        .def("initialize", (void (ActionParams::*)(ActionValidGetter&)) &
                               ActionParams::Initialize)
        .def("get_checker", &ActionParams::GetChecker)
        .def("choose_main_op", &ActionParams::ChooseMainOp)
        .def("get_minion_put_location", &ActionParams::GetMinionPutLocation)
        .def("get_specified_target", &ActionParams::GetSpecifiedTarget)
        .def("choose_one", &ActionParams::ChooseOne)
        .def("get_attacker", &ActionParams::GetAttacker)
        .def("get_number",
             (std::size_t(ActionParams::*)(ActionType, ActionChoices&)) &
                 ActionParams::GetNumber);
}
