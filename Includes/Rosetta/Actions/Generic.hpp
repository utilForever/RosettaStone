// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_GENERIC_HPP
#define ROSETTASTONE_GENERIC_HPP

#include <Rosetta/Models/Player.hpp>

namespace RosettaStone::Generic
{
//! Adds card to hand.
//! \param player The player to add card to hand.
//! \param entity A card to add.
void AddCardToHand(Player& player, Entity* entity);

//! Removes card from hand.
//! \param player The player to remove card from hand.
//! \param entity A card to remove.
void RemoveCardFromHand(Player& player, Entity* entity);

//! Changes mana crystal of the player.
//! \param player The player to change mana crystal.
//! \param amount A value indicating how much to change mana crystal.
//! \param fill true if mana crystal is filled, and false otherwise.
void ChangeManaCrystal(Player& player, int amount, bool fill);

//! Transforms a minion to another.
//! \param player The owner of minion to transform.
//! \param oldMinion An old minion to transform.
//! \param card A new card ID to transform.
void TransformMinion(Player& player, Minion* oldMinion, Card card);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_GENERIC_HPP
