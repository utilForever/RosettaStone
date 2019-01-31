// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_GENERIC_HPP
#define HEARTHSTONEPP_GENERIC_HPP

#include <hspp/Models/Entity.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp
{
//!
//! \brief Generic class.
//!
//! This class is a container of game logic functionality.
//!
class Generic
{
 public:
    //! Draws a \p card to \p player.
    //! \param player The player to create card.
    //! \param card An object that is stored card information.
    //! \return A dynamic allocated card object.
    static Entity* DrawCard(Player& player, Card&& card);
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GENERIC_HPP
