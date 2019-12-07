// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Conditions/SelfCondition.hpp>
#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Models/Playable.hpp>

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;

void AddSelfCondition(pybind11::module& m)
{
    pybind11::class_<SelfCondition>(
        m, "SelfCondition",
        R"pbdoc(This class is a container for all conditions about the subject entity.)pbdoc")
        .def(pybind11::init<std::function<bool(Playable*)>>(),
             R"pbdoc(Constructs task with given func.

             Parameters
             ----------
             - func : The function to check condition.)pbdoc",
             pybind11::arg("func"))
        .def_static(
            "is_hero_power_card", &SelfCondition::IsHeroPowerCard,
            R"pbdoc(SelfCondition wrapper for checking the hero power equals card_id.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - card_id : The card ID of hero power.)pbdoc",
            pybind11::arg("card_id"))
        .def_static(
            "is_dead", &SelfCondition::IsDead,
            R"pbdoc(SelfCondition wrapper for checking the entity is destroyed.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "Is_not_dead", &SelfCondition::IsNotDead,
            R"pbdoc(SelfCondition wrapper for checking the entity is not destroyed.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_fiedl_full", &SelfCondition::IsFieldFull,
            R"pbdoc(SelfCondition wrapper for checking the field is full.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_damaged", &SelfCondition::IsDamaged,
            R"pbdoc(SelfCondition wrapper for checking the entity is damaged.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_undamaged", &SelfCondition::IsUndamaged,
            R"pbdoc(SelfCondition wrapper for checking the entity is undamaged.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_weapon_equipped", &SelfCondition::IsWeaponEquipped,
            R"pbdoc(SelfCondition wrapper for checking the hero equips weapon.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_race", &SelfCondition::IsRace,
            R"pbdoc(SelfCondition wrapper for checking race of entity is race.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - race : The race for checking.)pbdoc",
            pybind11::arg("race"))
        .def_static(
            "is_controlling_race", &SelfCondition::IsControllingRace,
            R"pbdoc(SelfCondition wrapper for checking there is the entity with race in field zone.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - race : The race for checking.)pbdoc",
            pybind11::arg("race"))
        .def_static(
            "is_controlling_secret", &SelfCondition::IsControllingSecret,
            R"pbdoc(SelfCondition wrapper for checking the secret exists in the owner's secret zone.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_minion", &SelfCondition::IsMinion,
            R"pbdoc(SelfCondition wrapper for checking the entity is minion.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_spell", &SelfCondition::IsSpell,
            R"pbdoc(SelfCondition wrapper for checking the entity is spell.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_secret", &SelfCondition::IsSecret,
            R"pbdoc(SelfCondition wrapper for checking the entity is secret.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_frozen", &SelfCondition::IsFrozen,
            R"pbdoc(SelfCondition wrapper for checking the entity is frozen.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "has_minion_in_hand", &SelfCondition::HasMinionInHand,
            R"pbdoc(SelfCondition wrapper for checking the player has minion in hand.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "is_overload_card", &SelfCondition::IsOverloadCard,
            R"pbdoc(SelfCondition wrapper for checking the card has overload.

            Generated SelfCondition for intended purpose.)pbdoc")
        .def_static(
            "minions_played_this_turn", &SelfCondition::MinionsPlayedThisTurn,
            R"pbdoc(SelfCondition wrapper for checking the number of minion that played this turn.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - num : The number of minion for checking.)pbdoc",
            pybind11::arg("num"))
        .def_static(
            "is_tag_value", &SelfCondition::IsTagValue,
            R"pbdoc(SelfCondition wrapper for checking there is the entity that satisfies condition with tag, value and rela_sign.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - tag : The game tag to check condition.
            - value : The value to check condition.
            - rela_sign : The comparer to check condition.)pbdoc",
            pybind11::arg("tag"), pybind11::arg("value"),
            pybind11::arg("rela_sign"))
        .def_static(
            "is_name", &SelfCondition::IsName,
            R"pbdoc(SelfCondition wrapper for checking the name of entity equals name.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - name : The name of card to check condition.
            - is_equal : The flag to indicate that the condition for equality.)pbdoc",
            pybind11::arg("name"), pybind11::arg("is_equal"))
        .def_static(
            "is_stack_num", &SelfCondition::IsStackNum,
            R"pbdoc(SelfCondition wrapper for checking num in taskStack satisfy condition with value and rela_sign.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - value : The value to check condition.
            - rela_sign : The comparer to check condition.
            - index : If index is 0, use num; I findex is 1, use num1)pbdoc",
            pybind11::arg("value"), pybind11::arg("rela_sign"),
            pybind11::arg("index"))
        .def_static(
            "is_health", &SelfCondition::IsHealth,
            R"pbdoc(SelfCondition wrapper for checking the health that satisfies condition with value and rela_sign.

            Generated SelfCondition for intended purpose.

            Parameters
            ----------
            - value : The value to check condition.
            - rela_sign : The comparer to check condition.)pbdoc",
            pybind11::arg("value"), pybind11::arg("rela_sign"))
        .def("Evaluate", &SelfCondition::Evaluate,
             R"pbdoc(Evaluates condition using checking function.

             true if the condition is satisfied, false otherwise.

             Parameters
             ----------
             - owner : The owner entity.)pbdoc",
             pybind11::arg("owner"));
}
