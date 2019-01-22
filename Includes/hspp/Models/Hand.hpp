// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HAND_HPP
#define HEARTHSTONEPP_HAND_HPP

#include <hspp/Cards/Entity.hpp>
#include <hspp/Commons/Constants.hpp>

#include <array>

namespace Hearthstonepp
{
//!
//! \brief Hand class.
//!
//! This class is where  each player keeps the cards currently available to
//! them. The player can see their hand face-up at the bottom of the screen,
//! while the opponent's hand is shown face-down at the top of the screen.
//!
class Hand
{
 public:
 private:
    std::array<Entity*, MAXIMUM_NUM_CARDS_IN_HAND> m_cards{};
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_HAND_HPP