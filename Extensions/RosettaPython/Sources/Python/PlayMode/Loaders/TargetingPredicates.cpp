// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Loaders/TargetingPredicates.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Loaders/TargetingPredicates.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone::PlayMode;

void AddTargetingPredicates(pybind11::module& m)
{
    pybind11::class_<TargetingPredicates>(
        m, "TargetingPredicates",
        R"pbdoc(This class includes utility methods for targeting predicate.)pbdoc")
        .def_static(
            "req_murloc_target", &TargetingPredicates::ReqMurlocTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::MURLOC.)pbdoc")
        .def_static(
            "req_demon_target", &TargetingPredicates::ReqDemonTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::DEMON.)pbdoc")
        .def_static(
            "req_mechanical_target", &TargetingPredicates::ReqMechanicalTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::MECHANICAL.)pbdoc")
        .def_static(
            "req_elemental_target", &TargetingPredicates::ReqElementalTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::ELEMENTAL.)pbdoc")
        .def_static(
            "req_beast_target", &TargetingPredicates::ReqBeastTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::BEAST.)pbdoc")
        .def_static(
            "req_totem_target", &TargetingPredicates::ReqTotemTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::TOTEM.)pbdoc")
        .def_static(
            "req_pirate_target", &TargetingPredicates::ReqPirateTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::PIRATE.)pbdoc")
        .def_static(
            "req_dragon_target", &TargetingPredicates::ReqDragonTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it has Race::DRAGON.)pbdoc")
        .def_static(
            "req_target_with_race", &TargetingPredicates::ReqTargetWithRace,
            R"pbdoc(Predicate wrapper for checking the target requires that it has race.

            Parameters
            ----------
            race : The value of race.)pbdoc")
        .def_static(
            "req_damaged_target", &TargetingPredicates::ReqDamagedTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it is damaged.)pbdoc")
        .def_static(
            "req_undamaged_target", &TargetingPredicates::ReqUndamagedTarget,
            R"pbdoc(Predicate wrapper for checking the target requires that it is undamabed.)pbdoc")
        .def_static(
            "req_target_max_attack", &TargetingPredicates::ReqTargetMaxAttack,
            R"pbdoc(Predicate wrapper for checking the target requires that the maximum attack is value.

            Parameters
            ----------
            value : The value of maximum attack.)pbdoc")
        .def_static(
            "req_target_min_attack", &TargetingPredicates::ReqTargetMinAttack,
            R"pbdoc(Predicate wrapper for checking the target requires that the minimum attack is value.

            Parameters
            ----------
            value : The value of minimum attack.)pbdoc")
        .def_static(
            "req_target_for_combo", &TargetingPredicates::ReqTargetForCombo,
            R"pbdoc(Predicate wrapper for checking the target requires combo active.)pbdoc")
        .def_static(
            "req_must_target_taunter",
            &TargetingPredicates::ReqMustTargetTaunter,
            R"pbdoc(Predicate wrapper for checking the target requires that it has taunt.)pbdoc");
}
