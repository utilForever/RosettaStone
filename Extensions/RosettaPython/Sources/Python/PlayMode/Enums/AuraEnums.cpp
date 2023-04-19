// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Enums/AuraEnums.hpp>
#include <Rosetta/Common/Enums/AuraEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddAuraEnums(pybind11::module& m)
{
    pybind11::enum_<AuraType>(
        m, "AuraType", R"pbdoc(An enumerator for identifying aura type.)pbdoc")
        .value("INVALID", AuraType::INVALID, R"pbdoc(Invalid type.)pbdoc")
        .value(
            "SELF", AuraType::SELF,
            R"pbdoc(This type of aura only affects the source of the aura.)pbdoc")
        .value(
            "ADJACENT", AuraType::ADJACENT,
            R"pbdoc(This type of aura affects the minions adjacent to the source of the aura.)pbdoc")
        .value("FIELD", AuraType::FIELD,
               R"pbdoc(This type of aura affects all friendly minions.)pbdoc")
        .value(
            "FIELD_EXCEPT_SOURCE", AuraType::FIELD_EXCEPT_SOURCE,
            R"pbdoc(This type of aura affects all friendly minions except the source of the aura.)pbdoc")
        .value(
            "HERO", AuraType::HERO,
            R"pbdoc(This type of aura affects the source's controller.)pbdoc")
        .value(
            "WEAPON", AuraType::WEAPON,
            R"pbdoc(This type of aura affects the weapon of the source's controller.)pbdoc")
        .value(
            "HAND", AuraType::HAND,
            R"pbdoc(This type of aura affects all entities in the hand of the source's controller.)pbdoc")
        .value(
            "ENEMY_HAND", AuraType::ENEMY_HAND,
            R"pbdoc(This type of aura affects all entities in the hand of the opponent of the source's controller.)pbdoc")
        .value(
            "HANDS", AuraType::HAND,
            R"pbdoc(This type of aura affects all entities in the both player's hand.)pbdoc")
        .value(
            "FIELD_AND_HAND", AuraType::FIELD_AND_HAND,
            R"pbdoc(This type of aura affects all friendly minions and entities in the hand of the source's controller.)pbdoc");

    pybind11::enum_<AuraInstruction>(
        m, "AuraInstruction",
        R"pbdoc(An enumerator for identifying instruction of aura update.)pbdoc")
        .value("INVALID", AuraInstruction::INVALID)
        .value("ADD", AuraInstruction::ADD)
        .value("ADD_ALL", AuraInstruction::ADD_ALL)
        .value("REMOVE", AuraInstruction::REMOVE)
        .value("REMOVE_ALL", AuraInstruction::REMOVE_ALL);
}
