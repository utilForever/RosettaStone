// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Enums/TriggerEnums.hpp>
#include <Rosetta/Common/Enums/TriggerEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddTriggerEnums(pybind11::module& m)
{
    pybind11::enum_<TriggerType>(
        m, "TriggerType",
        R"pbdoc(An enumerator for identifying trigger type.)pbdoc")
        .value("NONE", TriggerType::NONE,
               R"pbdoc(The effect has nothing.)pbdoc")
        .value(
            "TURN_START", TriggerType::TURN_START,
            R"pbdoc(The effect will be triggered at the start of turn.)pbdoc")
        .value("TURN_END", TriggerType::TURN_END,
               R"pbdoc(The effect will be triggered at the end of turn.)pbdoc")
        .value(
            "PLAY_CARD", TriggerType::PLAY_CARD,
            R"pbdoc(The effect will be triggered when a player plays a card.)pbdoc")
        .value(
            "CAST_SPELL", TriggerType::CAST_SPELL,
            R"pbdoc(The effect will be triggered when a player plays a Spell card.)pbdoc")
        .value(
            "AFTER_CAST", TriggerType::AFTER_CAST,
            R"pbdoc(The effect will be triggered after a spell is played.)pbdoc")
        .value(
            "GIVE_HEAL", TriggerType::GIVE_HEAL,
            R"pbdoc(The effect will be triggered when a playable heals a character.)pbdoc")
        .value(
            "TAKE_HEAL", TriggerType::TAKE_HEAL,
            R"pbdoc(The effect will be triggered when a character is healed.)pbdoc")
        .value(
            "ATTACK", TriggerType::ATTACK,
            R"pbdoc(The effect will be triggered when characters attack.)pbdoc")
        .value(
            "AFTER_ATTACK", TriggerType::AFTER_ATTACK,
            R"pbdoc(The effect will be triggered after an attack action is ended.)pbdoc")
        .value(
            "SUMMON", TriggerType::SUMMON,
            R"pbdoc(The effect will be triggered whenever a minion is summoned.)pbdoc")
        .value(
            "AFTER_SUMMON", TriggerType::AFTER_SUMMON,
            R"pbdoc(The effect will be triggered after a minion is summoned.)pbdoc")
        .value(
            "PLAY_MINION", TriggerType::PLAY_MINION,
            R"pbdoc(The effect will be triggered when a player plays a Minion card.)pbdoc")
        .value(
            "AFTER_PLAY_MINION", TriggerType::AFTER_PLAY_MINION,
            R"pbdoc(The effect will be triggered after a minion is played.)pbdoc")
        .value(
            "DEAL_DAMAGE", TriggerType::DEAL_DAMAGE,
            R"pbdoc(The effect will be triggered when a character is damaged.)pbdoc")
        .value(
            "TAKE_DAMAGE", TriggerType::TAKE_DAMAGE,
            R"pbdoc(The effect will be triggered when a spell or a character deals damages to source.)pbdoc")
        .value(
            "PREDAMAGE", TriggerType::PREDAMAGE,
            R"pbdoc(Effect will be triggered when a character gets predamage. This event happens just before the character is actually damaged.)pbdoc")
        .value(
            "TARGET", TriggerType::TARGET,
            R"pbdoc(The effect will be triggered when a card is targeted by an attacking minion or a played card.)pbdoc")
        .value("DEATH", TriggerType::DEATH,
               R"pbdoc(The effect will be triggered when a minion dies.)pbdoc");

    pybind11::enum_<TriggerSource>(
        m, "TriggerSource",
        R"pbdoc(An enumerator for identifying trigger source.)pbdoc")
        .value("NONE", TriggerSource::NONE)
        .value("SELF", TriggerSource::SELF)
        .value("ENEMY", TriggerSource::ENEMY)
        .value("HERO", TriggerSource::HERO)
        .value("ALL_MINIONS", TriggerSource::ALL_MINIONS)
        .value("MINIONS", TriggerSource::MINIONS)
        .value("MINIONS_EXCEPT_SELF", TriggerSource::MINIONS_EXCEPT_SELF)
        .value("ENEMY_MINIONS", TriggerSource::ENEMY_MINIONS)
        .value("ENCHANTMENT_TARGET", TriggerSource::ENCHANTMENT_TARGET)
        .value("ENEMY_SPELLS", TriggerSource::ENEMY_SPELLS)
        .value("FRIENDLY", TriggerSource::FRIENDLY);

    pybind11::enum_<TriggerActivation>(
        m, "TriggerAction",
        R"pbdoc(An enumerator for identifying trigger activation.)pbdoc")
        .value("PLAY", TriggerActivation::PLAY)
        .value("HAND", TriggerActivation::HAND)
        .value("DECK", TriggerActivation::DECK)
        .value("HAND_OR_PLAY", TriggerActivation::HAND_OR_PLAY);

    pybind11::enum_<SequenceType>(
        m, "SequenceType",
        R"pbdoc(An enumerator for identifying sequence type.)pbdoc")
        .value("NONE", SequenceType::NONE)
        .value("PLAY_CARD", SequenceType::PLAY_CARD)
        .value("PLAY_MINION", SequenceType::PLAY_MINION)
        .value("PLAY_SPELL", SequenceType::PLAY_SPELL)
        .value("TARGET", SequenceType::TARGET);
}
