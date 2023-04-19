// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Enums/TargetingEnums.hpp>
#include <Rosetta/Common/Enums/TargetingEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddTargetingEnums(pybind11::module& m)
{
    pybind11::enum_<TargetingType>(
        m, "TargetingType",
        R"pbdoc(An enumerator for identifying targeting type.)pbdoc")
        .value("NONE", TargetingType::NONE)
        .value("ALL", TargetingType::ALL)
        .value("FRIENDLY_CHARACTERS", TargetingType::FRIENDLY_CHARACTERS)
        .value("ENEMY_CHARACTERS", TargetingType::ENEMY_CHARACTERS)
        .value("ALL_MINIONS", TargetingType::ALL_MINIONS)
        .value("FRIENDLY_MINIONS", TargetingType::FRIENDLY_MINIONS)
        .value("ENEMY_MINIONS", TargetingType::ENEMY_MINIONS)
        .value("HEROS", TargetingType::HEROES);

    pybind11::enum_<CharacterType>(
        m, "CharacterType",
        R"pbdoc(An enumerator for identifying character type.)pbdoc")
        .value("CHARACTERS", CharacterType::CHARACTERS)
        .value("HEROES", CharacterType::HEROES)
        .value("MINIONS", CharacterType::MINIONS);

    pybind11::enum_<FriendlyType>(
        m, "FriendlyType",
        R"pbdoc(An enumerator for identifying friendly type.)pbdoc")
        .value("ALL", FriendlyType::ALL)
        .value("FRIENDLY", FriendlyType::FRIENDLY)
        .value("ENEMY", FriendlyType::ENEMY);
}
