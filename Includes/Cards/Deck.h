#ifndef HEARTHSTONEPP_DECK_H
#define HEARTHSTONEPP_DECK_H

#include <Cards/Card.h>
#include <Cards/Cards.h>
#include <Enums/CardEnums.h>

#include <string>

namespace Hearthstonepp
{
//!
//! \brief Deck class.
//!
//! This class stores a deck. A deck is a collection of exactly 30 cards
//! assembled before a match, as well as the zone which players draw cards from
//! (and sometimes add cards to) during gameplay. Each deck is tied to a
//! specific class.
//!
class Deck
{
 public:
    //! Default constructor.
    Deck();

    //! Constructs deck with given \p name and \p deckClass.
    //! \param name The name of deck.
    //! \param deckClass The class of deck.
    Deck(std::string name, const CardClass deckClass);

    //! Returns the name of deck.
    //! \return The name of deck.
    std::string GetName() const;

    //! Returns the class of deck.
    //! \return The class of deck.
    CardClass GetClass() const;

    //! Returns the number of cards in deck.
    //! \return The number of cards in deck.
    unsigned int GetNumOfCards() const;

    //! Returns the unique number of cards in deck.
    //! \return The unique number of cards in deck.
    size_t GetUniqueNumOfCards() const;

    //! Returns the number of cards in deck that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return The number of cards in deck that matches \p cardID.
    unsigned int GetNumCardInDeck(std::string cardID);


    //! Creates a deck from a list of pointers to cards to play game.
    //! \return A deck from a list of pointers to cards.
    std::vector<const Card*> GetPrimitiveDeck() const;

    //! Returns card ID and the number of card at \p idx in deck.
    //! \param idx Index of cards in deck.
    //! \return card ID and the number of card at \p idx in deck.
    std::pair<std::string, int> GetCard(size_t idx) const;

    //! Prints card list in deck.
    void ShowCardList() const;

    //! Add card(s) to deck with given \p cardID and \p numCardToAdd.
    //! \param cardID The ID of the card to add to deck.
    //! \param numCardToAdd The number of card to add to deck.
    //! \return true if card(s) is added to deck successfully, and false otherwise.
    bool AddCard(std::string cardID, int numCardToAdd);

    //! Delete card(s) from deck with given \p cardID and \p numCardToDelete.
    //! \param cardID The ID of the card to delete from deck.
    //! \param numCardToDelete The number of card to delete from deck.
    //! \return true if card(s) is deleted from deck successfully, and false otherwise.
    bool DeleteCard(std::string cardID, const int numCardToDelete);

 private:
    std::string m_name;
    CardClass m_class;

    unsigned int m_numOfCards;
    std::vector<std::pair<std::string, int>> m_cards;
};
}

#endif