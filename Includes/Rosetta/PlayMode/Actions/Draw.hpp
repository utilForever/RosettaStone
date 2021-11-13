// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DRAW_HPP
#define ROSETTASTONE_PLAYMODE_DRAW_HPP

#include <Rosetta/PlayMode/Models/Entity.hpp>

namespace RosettaStone::PlayMode::Generic
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

//! Finds another spell card from the deck.
//! \param player The player to find another spell card from the deck.
Playable* FindAnotherSpellCard(const Player* player);
}  // namespace RosettaStone::PlayMode::Generic

#endif  // ROSETTASTONE_PLAYMODE_DRAW_HPP
