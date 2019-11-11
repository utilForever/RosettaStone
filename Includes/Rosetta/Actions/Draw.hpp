// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_DRAW_HPP
#define ROSETTASTONE_DRAW_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone::Generic
{
//! Draws a card in the deck.
//! \param player The player to add card to the hand.
//! \param cardToDraw A card to draw in the deck.
//! \return A dynamic allocated entity object.
Playable* Draw(Player* player, Playable* cardToDraw = nullptr);

//! Draws a specific card to the hand.
//! \param player The player to add card to the hand.
//! \param card A card to draw to the hand.
//! \return A dynamic allocated entity object.
Playable* DrawCard(Player* player, Card* card);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_DRAW_HPP
