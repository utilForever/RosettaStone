// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/Enums/TriggerEnums.hpp>
#include <Rosetta/Enums/TriggerEnums.hpp>

#include <pybind11/pybind11.h>

using namespace RosettaStone;

void AddTriggerEnums(pybind11::module& m)
{
    pybind11::enum_<TriggerType>(m, "TriggerType")
        .value("NONE", TriggerType::NONE)
        .value("TURN_START", TriggerType::TURN_START)
        .value("TURN_END", TriggerType::TURN_END)
        .value("PLAY_CARD", TriggerType::PLAY_CARD)
        .value("CAST_SPELL", TriggerType::CAST_SPELL)
        .value("AFTER_CAST", TriggerType::AFTER_CAST)
        .value("HEAL", TriggerType::HEAL)
        .value("ATTACK", TriggerType::ATTACK)
        .value("AFTER_ATTACK", TriggerType::AFTER_ATTACK)
        .value("SUMMON", TriggerType::SUMMON)
        .value("AFTER_SUMMON", TriggerType::AFTER_SUMMON)
        .value("PLAY_MINION", TriggerType::PLAY_MINION)
        .value("AFTER_PLAY_MINION", TriggerType::AFTER_PLAY_MINION)
        .value("DEAL_DAMAGE", TriggerType::DEAL_DAMAGE)
        .value("TAKE_DAMAGE", TriggerType::TAKE_DAMAGE)
        .value("PREDAMAGE", TriggerType::PREDAMAGE)
        .value("TARGET", TriggerType::TARGET)
        .value("DEATH", TriggerType::DEATH);

    pybind11::enum_<TriggerSource>(m, "TriggerSource")
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

    pybind11::enum_<TriggerActivation>(m, "TriggerAction")
        .value("PLAY", TriggerActivation::PLAY)
        .value("HAND", TriggerActivation::HAND)
        .value("DECK", TriggerActivation::DECK)
        .value("HAND_OR_PLAY", TriggerActivation::HAND_OR_PLAY);

    pybind11::enum_<SequenceType>(m, "SequenceType")
        .value("NONE", SequenceType::NONE)
        .value("PLAY_CARD", SequenceType::PLAY_CARD)
        .value("PLAY_MINION", SequenceType::PLAY_MINION)
        .value("PLAY_SPELL", SequenceType::PLAY_SPELL)
        .value("TARGET", SequenceType::TARGET);
}
