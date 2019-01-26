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
    //! Default constructor.
    Hand();

    //! Returns the owner of hand.
    //! \return The owner of hand.
    Player& GetOwner() const;

    //! Sets the owner of hand.
    //! \param owner The owner of hand.
    void SetOwner(Player& owner);

    //! Returns the number of cards in hand.
    //! \return The number of cards in hand.
    std::size_t GetNumOfCards() const;

    //! Adds a card to hand.
    //! \param card The card to add to hand.
    void AddCard(Entity& card);

 private:
    Player* m_owner = nullptr;
    std::array<Entity*, HAND_SIZE> m_cards{};

    int m_numCard = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_HAND_HPP