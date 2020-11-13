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
    CHOOSE_ONE,
    FOUR_COST_CARD,
    SIX_COST_MINION_SUMMON,
    LEGENDARY_MINION_SUMMON,
    TAUNT_MINION,
    DEATHRATTLE_MINION,
    DEATHRATTLE_MINION_DIED,
    SPELLPOWER_MINION,
    RUSH_MINION,
    SPELL,
    SPELL_THREE_COST_OR_LESS,
    DEMON,
    DRAGON,
    HEISTBARON_TOGWAGGLE,
    MADAME_LAZUL,
    SWAMPQUEEN_HAGATHA,
    TORTOLLAN_PILGRIM,
    JANDICE_BAROV,
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
