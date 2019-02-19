// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_HAND_HPP
#define HEARTHSTONEPP_HAND_HPP

#include <hspp/Commons/Constants.hpp>
#include <hspp/Models/Entity.hpp>

#include <array>

namespace Hearthstonepp
{
//!
//! \brief Hand class.
//!
//! This class is where each player keeps the cards currently available to
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

    //! Finds out if hand is full.
    //! \return true if hand is full, and false otherwise.
    bool IsFull() const;

    //! Finds out if hand is empty.
    //! \return true if hand is empty, and false otherwise.
    bool IsEmpty() const;

    //! Returns the number of cards in hand.
    //! \return The number of cards in hand.
    std::size_t GetNumOfCards() const;

    //! Returns card in hand.
    //! \param pos The position of card in hand.
    //! \return A card in hand at \p pos.
    Entity* GetCard(std::size_t pos);

    //! Returns all cards in hand.
    //! \return A list of cards in hand.
    std::vector<Entity*> GetAllCards();

    //! Returns the position of card in hand.
    //! \return The position of card in hand.
    optional<std::size_t> FindCardPos(Entity& card);

    //! Adds a card to hand.
    //! \param card The card to add to hand.
    void AddCard(Entity& card);

    //! Removes a card from hand.
    //! \param card The card to remove from hand.
    void RemoveCard(Entity& card);

 private:
    Player* m_owner = nullptr;
    std::array<Entity*, HAND_SIZE> m_cards{};

    std::size_t m_numCard = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_HAND_HPP