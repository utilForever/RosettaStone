// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GENERIC_HPP
#define HEARTHSTONEPP_GENERIC_HPP

#include <hspp/Accounts/Player.hpp>
#include <hspp/Cards/Entity.hpp>

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
