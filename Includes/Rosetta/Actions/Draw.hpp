// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_DRAW_HPP
#define HEARTHSTONEPP_DRAW_HPP

#include <hspp/Models/Entity.hpp>

namespace Hearthstonepp::Generic
{
//! Draws a card in the deck.
//! \param player The player to add card to the hand.
//! \param cardToDraw A card to draw in the deck.
//! \return A dynamic allocated entity object.
Entity* Draw(Player& player, std::optional<Entity> cardToDraw = std::nullopt);

//! Draws a specific card to the hand.
//! \param player The player to add card to the hand.
//! \param card A card to draw to the hand.
//! \return A dynamic allocated entity object.
Entity* DrawCard(Player& player, Card&& card);
}  // namespace Hearthstonepp::Generic

#endif  // HEARTHSTONEPP_DRAW_HPP
