// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Conditions/RelaCondition.hpp>
#include <Rosetta/Conditions/RelaCondition.hpp>
#include <Rosetta/Models/Playable.hpp>

#include <pybind11/pybind11.h>

#include <pybind11/functional.h>
#include <pybind11/stl.h>

using namespace RosettaStone;

void AddRelaCondition(pybind11::module& m)
{
    pybind11::class_<RelaCondition>(
        m, "RelaCondition",
        R"pbdoc(This class is a container for all conditions about the relation between 2 entities.)pbdoc")
        .def(pybind11::init<std::function<bool(Playable*, Playable*)>>(),
             R"pbdoc(Constructs task with given func.

             Parameters
             ----------
             - func : The function to check condition.)pbdoc",
             pybind11::arg("func"))
        .def_static(
            "is_friendly", &RelaCondition::IsFriendly,
            R"pbdoc(RelaCondition wrapper for checking the entity is friendly.

            Generated RelaCondition for intended purpose.)pbdoc")
        .def_static(
            "is_side_by_side", &RelaCondition::IsSideBySide,
            R"pbdoc(RelaCondition wrapper for checking the entity is positioned side by side.

            Generated RelaCondition for intended purpose.)pbdoc")
        .def("evaluate", &RelaCondition::Evaluate,
             R"pbdoc(Evaluates condition using checking function.

             true if the condition is satisfied, false otherwise.

             Parameters
             ----------
             - owner : The owner entity.
             - affected : The affected entity.)pbdoc",
             pybind11::arg("owner"), pybind11::arg("affected"));
}
