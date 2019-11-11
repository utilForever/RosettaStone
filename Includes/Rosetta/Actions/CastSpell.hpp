// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_CAST_SPELL_HPP
#define ROSETTASTONE_CAST_SPELL_HPP

#include <Rosetta/Models/Character.hpp>
#include <Rosetta/Models/Spell.hpp>

namespace RosettaStone::Generic
{
//! Casts spell without/to target.
//! \param player The player to cast spell.
//! \param spell The spell to cast.
//! \param target The target of spell.
//! \param chooseOne The index of chosen card from two cards.
void CastSpell(Player* player, Spell* spell, Character* target, int chooseOne);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_CAST_SPELL_HPP
