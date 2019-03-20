// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_ATTACK_HPP
#define HEARTHSTONEPP_ATTACK_HPP

#include <Rosetta/Models/Player.hpp>

namespace RosettaStone::Generic
{
//! Source character attacks target character.
//! \param player An owner of source character.
//! \param source A pointer to source character.
//! \param target A pointer to target character.
void Attack(Player& player, Character* source, Character* target);
}  // namespace RosettaStone::Generic

#endif  // HEARTHSTONEPP_ATTACK_HPP
