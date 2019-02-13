// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_DRAW_HPP
#define HEARTHSTONEPP_DRAW_HPP

#include <hspp/Models/Entity.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp
{
//!
//! \brief Draw class.
//!
//! This class is a collection of card draw functions.
//!
class Draw
{
 public:
    //! Draws a \p card to \p player.
    //! \param player The player to create card.
    //! \param card An object that is stored card information.
    //! \return A dynamic allocated card object.
    static Entity* DrawCard(Player& player, Card&& card);
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_DRAW_HPP
