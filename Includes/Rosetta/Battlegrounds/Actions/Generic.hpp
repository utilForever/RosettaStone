// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_GENERIC_HPP
#define ROSETTASTONE_BATTLEGROUNDS_GENERIC_HPP

#include <Rosetta/Battlegrounds/Models/Minion.hpp>

namespace RosettaStone::Battlegrounds::Generic
{
//! Creates a new enchantment and attaches it to the given target.
//! \param enchantmentCard The base card for the enchantment.
//! \param target The target minion.
//! \param num The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
void AddEnchantment(Card& enchantmentCard, Minion& target, int num = -1);
}  // namespace RosettaStone::Battlegrounds::Generic

#endif  // ROSETTASTONE_BATTLEGROUNDS_GENERIC_HPP
