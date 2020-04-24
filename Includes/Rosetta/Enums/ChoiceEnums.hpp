// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CHOICE_ENUMS_HPP
#define ROSETTASTONE_CHOICE_ENUMS_HPP

namespace RosettaStone
{
//! The type of discover.
enum class DiscoverType
{
    INVALID,
    SPELL,
    DRAGON,
    LEGENDARY_MINION_SUMMON,
    SIX_COST_SUMMON,
    SPELL_THREE_COST_OR_LESS,
    HEISTBARON_TOGWAGGLE,
};

//! The action type of choice.
enum class ChoiceAction
{
    INVALID,            //!< Invalid action.
    HAND,               //!< Hand.
    ENCHANTMENT,        //!< Enchantment.
    CAST_SPELL,         //!< Cast spell.
    SUMMON,             //!< Summon.
    STACK,              //!< Stack.
    ENVOY_OF_LAZUL,     //!< Envoy Of Lazul.
    SIGHTLESS_WATCHER,  //!< Sightless Watcher.
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CHOICE_ENUMS_HPP
