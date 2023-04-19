// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Decks/Deck.hpp>

#include <algorithm>

namespace RosettaStone::PlayMode
{
Deck::Deck(const FormatType formatType, const CardClass deckClass)
    : m_formatType(formatType), m_class(deckClass)
{
    // Do nothing
}

FormatType Deck::GetFormatType() const
{
    return m_formatType;
}

CardClass Deck::GetClass() const
{
    return m_class;
}

std::size_t Deck::GetNumOfCards() const
{
    return m_numOfCards;
}

std::size_t Deck::GetUniqueNumOfCards() const
{
    return m_cards.size();
}

std::size_t Deck::GetNumCardInDeck(std::string cardID)
{
    const auto cardIter = std::find_if(
        m_cards.begin(), m_cards.end(),
        [&cardID](const std::pair<std::string, std::size_t>& elem) {
            return elem.first == cardID;
        });

    // A card is in deck
    if (cardIter != m_cards.end())
    {
        return (*cardIter).second;
    }

    return 0;
}

std::pair<std::string, std::size_t> Deck::GetCard(std::size_t idx) const
{
    return m_cards.at(idx);
}

std::array<Card*, START_DECK_SIZE> Deck::GetCards() const
{
    std::array<Card*, START_DECK_SIZE> deck{};
    std::size_t cardIdx = 0;

    for (const auto& [id, num] : m_cards)
    {
        Card* card = Cards::GetInstance().FindCardByID(id);

        for (std::size_t i = 0; i < num; ++i)
        {
            deck[cardIdx++] = card;
        }
    }

    return deck;
}

bool Deck::AddCard(std::string cardID, std::size_t numCardToAdd)
{
    const Card* card = Cards::GetInstance().FindCardByID(cardID);

    const CardClass cardClass = card->GetCardClass();
    if ((cardClass != GetClass() && cardClass != CardClass::NEUTRAL) ||
        card->GetMaxAllowedInDeck() < numCardToAdd)
    {
        return false;
    }

    const auto cardIter = std::find_if(
        m_cards.begin(), m_cards.end(),
        [&cardID](const std::pair<std::string, std::size_t>& elem) {
            return elem.first == cardID;
        });

    // A card is in deck
    if (cardIter != m_cards.end())
    {
        if (card->GetMaxAllowedInDeck() < (*cardIter).second + numCardToAdd)
            return false;

        (*cardIter).second += numCardToAdd;
    }
    else
    {
        m_cards.emplace_back(std::make_pair(cardID, numCardToAdd));
    }

    m_numOfCards += numCardToAdd;

    return true;
}

bool Deck::DeleteCard(std::string cardID, std::size_t numCardToDelete)
{
    const auto cardIter = std::find_if(
        m_cards.begin(), m_cards.end(),
        [&cardID](const std::pair<std::string, std::size_t>& elem) {
            return elem.first == cardID;
        });

    // A card is in deck
    if (cardIter != m_cards.end())
    {
        // Remove a given number of cards from deck
        (*cardIter).second = std::min((*cardIter).second - numCardToDelete,
                                      static_cast<std::size_t>(0u));
        m_numOfCards = std::min(m_numOfCards - numCardToDelete,
                                static_cast<std::size_t>(0u));

        // If the number of cards is less than 0, remove card from deck
        if ((*cardIter).second <= 0)
        {
            m_cards.erase(cardIter);
        }

        return true;
    }

    return false;
}

std::vector<std::string> Deck::GetCardIDs() const
{
    std::vector<std::string> ret;
    ret.reserve(m_numOfCards);

    for (const auto& card : m_cards)
    {
        for (std::size_t i = 0; i < card.second; ++i)
        {
            ret.emplace_back(card.first);
        }
    }

    return ret;
}
}  // namespace RosettaStone::PlayMode
