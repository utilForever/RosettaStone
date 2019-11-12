// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Enums/AuraEnums.hpp>
#include <Rosetta/Enums/AuraEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddAuraEnums(pybind11::module& m)
{
    pybind11::enum_<AuraType>(m, "AuraType")
        .value("INVALID", AuraType::INVALID)
        .value("SELF", AuraType::SELF)
        .value("ADJACENT", AuraType::ADJACENT)
        .value("FIELD", AuraType::FIELD)
        .value("FIELD_EXCEPT_SOURCE", AuraType::FIELD_EXCEPT_SOURCE)
        .value("HERO", AuraType::HERO)
        .value("WEAPON", AuraType::WEAPON)
        .value("HAND", AuraType::HAND)
        .value("ENEMY_HAND", AuraType::ENEMY_HAND)
        .value("HANDS", AuraType::HAND)
        .value("FIELD_AND_HAND", AuraType::FIELD_AND_HAND);

    pybind11::enum_<AuraInstruction>(m, "AuraInstruction")
        .value("INVALID", AuraInstruction::INVALID)
        .value("ADD", AuraInstruction::ADD)
        .value("ADD_ALL", AuraInstruction::ADD_ALL)
        .value("REMOVE", AuraInstruction::REMOVE)
        .value("REMOVE_ALL", AuraInstruction::REMOVE_ALL);
}
