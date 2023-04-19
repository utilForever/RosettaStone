// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Enums/TaskEnums.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddTaskEnums(pybind11::module& m)
{
    pybind11::enum_<PowerType>(
        m, "PowerType",
        R"pbdoc(An enumerator for identifying power type.)pbdoc")
        .value("POWER", PowerType::POWER)
        .value("DEATHRATTLE", PowerType::DEATHRATTLE)
        .value("COMBO", PowerType::COMBO);

    pybind11::enum_<EntityType>(
        m, "EntityType",
        R"pbdoc(An enumerator for identifying entity type.)pbdoc")
        .value("INVALID", EntityType::INVALID)
        .value("SOURCE", EntityType::SOURCE)
        .value("TARGET", EntityType::TARGET)
        .value("ALL", EntityType::ALL)
        .value("ALL_NOSOURCE", EntityType::ALL_NOSOURCE)
        .value("FRIENDS", EntityType::FRIENDS)
        .value("ENEMIES", EntityType::ENEMIES)
        .value("ENEMIES_NOTARGET", EntityType::ENEMIES_NOTARGET)
        .value("HERO", EntityType::HERO)
        .value("ENEMY_HERO", EntityType::ENEMY_HERO)
        .value("WEAPON", EntityType::WEAPON)
        .value("ENEMY_WEAPON", EntityType::ENEMY_WEAPON)
        .value("HAND", EntityType::HAND)
        .value("ENEMY_HAND", EntityType::ENEMY_HAND)
        .value("DECK", EntityType::DECK)
        .value("ENEMY_DECK", EntityType::ENEMY_DECK)
        .value("ALL_MINIONS", EntityType::ALL_MINIONS)
        .value("ALL_MINIONS_NOSOURCE", EntityType::ALL_MINIONS_NOSOURCE)
        .value("MINIONS", EntityType::MINIONS)
        .value("MINIONS_NOSOURCE", EntityType::MINIONS_NOSOURCE)
        .value("ENEMY_MINIONS", EntityType::ENEMY_MINIONS)
        .value("STACK", EntityType::STACK)
        .value("PLAYER", EntityType::PLAYER)
        .value("ENEMY_PLAYER", EntityType::ENEMY_PLAYER);

    pybind11::enum_<RelaSign>(
        m, "RelaSign",
        R"pbdoc(An enumerator for evaluating the relation between primitive values during game simulation.)pbdoc")
        .value("EQ", RelaSign::EQ, R"pbdoc(Equal.)pbdoc")
        .value("GEQ", RelaSign::GEQ, R"pbdoc(Greater equal.)pbdoc")
        .value("LEQ", RelaSign::LEQ, R"pbdoc(Lesser equal.)pbdoc");
}
