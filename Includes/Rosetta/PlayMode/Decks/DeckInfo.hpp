// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_DECK_INFO_HPP
#define ROSETTASTONE_PLAYMODE_DECK_INFO_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>

#include <string>

namespace RosettaStone::PlayMode
{
//!
//! \brief DeckInfo class.
//!
//! This class stores deck information that contains exactly 30 cards.
//! This information imports/exports from/to json file.
//!
class DeckInfo
{
 public:
    //! Default constructor.
    DeckInfo();

    //! Constructs deck with given \p name and \p deckClass.
    //! \param name The name of deck.
    //! \param deckClass The class of deck.
    DeckInfo(std::string name, CardClass deckClass);

    //! Returns the name of deck.
    //! \return The name of deck.
    std::string GetName() const;

    //! Returns the class of deck.
    //! \return The class of deck.
    CardClass GetClass() const;

    //! Returns the number of cards in deck.
    //! \return The number of cards in deck.
    std::size_t GetNumOfCards() const;

    //! Returns the unique number of cards in deck.
    //! \return The unique number of cards in deck.
    std::size_t GetUniqueNumOfCards() const;

    //! Returns the number of cards in deck that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return The number of cards in deck that matches \p cardID.
    std::size_t GetNumCardInDeck(std::string cardID);

    //! Creates a deck from a list of pointers to cards to play game.
    //! \return A deck from a list of pointers to cards.
    std::vector<Card*> GetPrimitiveDeck() const;

    //! Returns card ID and the number of card at \p idx in deck.
    //! \param idx Index of cards in deck.
    //! \return card ID and the number of card at \p idx in deck.
    std::pair<std::string, std::size_t> GetCard(std::size_t idx) const;

    //! Prints card list in deck.
    void ShowCardList() const;

    //! Add card(s) to deck with given \p cardID and \p numCardToAdd.
    //! \param cardID The ID of the card to add to deck.
    //! \param numCardToAdd The number of card to add to deck.
    //! \return true if card(s) is added to deck successfully, and false
    //! otherwise.
    bool AddCard(std::string cardID, std::size_t numCardToAdd);

    //! Delete card(s) from deck with given \p cardID and \p numCardToDelete.
    //! \param cardID The ID of the card to delete from deck.
    //! \param numCardToDelete The number of card to delete from deck.
    //! \return true if card(s) is deleted from deck successfully, and false
    //! otherwise.
    bool DeleteCard(std::string cardID, std::size_t numCardToDelete);

    //! Returns a list of card IDs.
    //! \return A list of card IDs.
    std::vector<std::string> GetCardIDs();

 private:
    std::string m_name;
    CardClass m_class = CardClass::INVALID;

    std::size_t m_numOfCards = 0;
    std::vector<std::pair<std::string, std::size_t>> m_cards;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_DECK_INFO_HPP
