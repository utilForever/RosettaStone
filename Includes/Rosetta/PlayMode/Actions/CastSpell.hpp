// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CAST_SPELL_HPP
#define ROSETTASTONE_PLAYMODE_CAST_SPELL_HPP

#include <Rosetta/PlayMode/Models/Character.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>

namespace RosettaStone::PlayMode::Generic
{
//! Casts target or non-target spell.
//! \param player The player to cast spell.
//! \param spell The spell to cast.
//! \param target The target of spell.
//! \param chooseOne The index of chosen card from two cards.
void CastSpell(Player* player, Spell* spell, Character* target, int chooseOne);

//! Casts random spell with random target such as 'Puzzle Box of Yogg-Saron'.
//! \param player The player to cast spell.
//! \param spell The spell to cast.
//! \param target The target of spell.
//! \param chooseOne The index of chosen card from two cards.
void CastRandomSpell(Player* player, Spell* spell, Character* target,
                     int chooseOne);
}  // namespace RosettaStone::PlayMode::Generic

#endif  // ROSETTASTONE_PLAYMODE_CAST_SPELL_HPP
