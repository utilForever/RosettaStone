// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_GENERIC_HPP
#define HEARTHSTONEPP_GENERIC_HPP

#include <hspp/Models/Player.hpp>

namespace Hearthstonepp::Generic
{
//! Changes mana crystal of the player.
//! \param player The player to change mana crystal.
//! \param amount A value indicating how much to change mana crystal.
//! \param fill true if mana crystal is filled, and false otherwise.
void ChangeManaCrystal(Player& player, int amount, bool fill);
}  // namespace Hearthstonepp::Generic

#endif  // HEARTHSTONEPP_GENERIC_HPP