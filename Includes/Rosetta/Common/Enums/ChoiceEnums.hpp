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
    CHOOSE_ONE,
    DRAGON,
    LEGENDARY_MINION_SUMMON,
    DEATHRATTLE_MINION_DIED,
    SIX_COST_SUMMON,
    SPELL_THREE_COST_OR_LESS,
    HEISTBARON_TOGWAGGLE,
    MADAME_LAZUL,
    SWAMPQUEEN_HAGATHA,
    TORTOLLAN_PILGRIM,
    FOUR_COST_ONE,
};

//! The action type of choice.
enum class ChoiceAction
{
    INVALID,             //!< Invalid action.
    HAND,                //!< Hand.
    HAND_AND_STACK,      //!< Hand and stack.
    ENCHANTMENT,         //!< Enchantment.
    CAST_SPELL,          //!< Cast spell.
    SUMMON,              //!< Summon.
    STACK,               //!< Stack.
    ENVOY_OF_LAZUL,      //!< Envoy Of Lazul.
    SIGHTLESS_WATCHER,   //!< Sightless Watcher.
    SWAMPQUEEN_HAGATHA,  //!< Swampqueen Hagatha.
    TORTOLLAN_PILGRIM,   //!< Tortollan Pilgrim.
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CHOICE_ENUMS_HPP
