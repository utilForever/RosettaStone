// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_DECK_HPP
#define HEARTHSTONEPP_DECK_HPP

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Models/Entity.hpp>

#include <array>

namespace Hearthstonepp
{
//!
//! \brief Deck class.
//!
//! This class stores a deck. A deck is a collection of exactly 30 cards
//! assembled before a match, as well as the zone which players draw cards from
//! (and sometimes add cards to) during game play. Each deck is tied to a
//! specific class.
//!
class Deck
{
 public:
    //! Default constructor.
    Deck();

    //! Returns the owner of deck.
    //! \return The owner of deck.
    Player& GetOwner() const;

    //! Sets the owner of deck.
    //! \param owner The owner of deck.
    void SetOwner(Player& owner);

    //! Finds out if deck is empty.
    //! \return true if deck is empty, and false otherwise.
    bool IsEmpty() const;

    //! Returns the number of cards in deck.
    //! \return The number of cards in deck.
    std::size_t GetNumOfCards() const;

    //! Returns the top card from deck.
    //! \return The top card of deck.
    Entity* GetTopCard() const;

    //! Adds a card to deck.
    //! \param card The card to add to deck.
    void AddCard(Entity& card);

    //! Removes a card from deck.
    //! \param card The card to remove from deck.
    //! \return The card that is removed from deck.
    Entity& RemoveCard(Entity& card);

    //! Shuffles cards in deck.
    void Shuffle();

 private:
    Player* m_owner = nullptr;

    std::array<Entity*, MAX_DECK_SIZE> m_cards{};
    std::size_t m_numCard = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_DECK_HPP