// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Cards.h>
#include <hspp/Cards/Deck.h>

#include <algorithm>
#include <iostream>

namespace Hearthstonepp
{
Deck::Deck() : m_name("Empty")
{
    // Do nothing
}

Deck::Deck(std::string name, const CardClass deckClass)
    : m_name(std::move(name)), m_class(deckClass)
{
    // Do nothing
}

std::string Deck::GetName() const
{
    return m_name;
}

CardClass Deck::GetClass() const
{
    return m_class;
}

size_t Deck::GetNumOfCards() const
{
    return m_numOfCards;
}

size_t Deck::GetUniqueNumOfCards() const
{
    return m_cards.size();
}

size_t Deck::GetNumCardInDeck(std::string cardID)
{
    const auto cardIer =
        std::find_if(m_cards.begin(), m_cards.end(),
                     [&cardID](const std::pair<std::string, size_t>& elem) {
                         return elem.first == cardID;
                     });

    // A card is in deck
    if (cardIer != m_cards.end())
    {
        return (*cardIer).second;
    }

    return 0;
}

std::vector<Card> Deck::GetPrimitiveDeck() const
{
    std::vector<Card> deck;

    for (const auto& [id, num] : m_cards)
    {
        Card card = Cards::GetInstance().FindCardByID(id);

        for (size_t i = 0; i < num; ++i)
        {
            deck.push_back(card);
        }
    }

    return deck;
}

std::pair<std::string, size_t> Deck::GetCard(size_t idx) const
{
    return m_cards.at(idx);
}

void Deck::ShowCardList() const
{
    int idx = 1;

    for (auto& cardInfo : m_cards)
    {
        Card card = Cards::GetInstance().FindCardByID(cardInfo.first);
        if (card.id.empty())
        {
            continue;
        }

        std::cout << idx << ". ";
        card.ShowBriefInfo();
        std::cout << "(" << cardInfo.second << " card(s))\n";

        idx++;
    }
}

bool Deck::AddCard(std::string cardID, size_t numCardToAdd)
{
    Card card = Cards::GetInstance().FindCardByID(cardID);

    const CardClass cardClass = card.cardClass;
    if ((cardClass != GetClass() && cardClass != +CardClass::NEUTRAL) ||
        card.GetMaxAllowedInDeck() < numCardToAdd)
    {
        return false;
    }

    const auto cardIter =
        std::find_if(m_cards.begin(), m_cards.end(),
                     [&cardID](const std::pair<std::string, size_t>& elem) {
                         return elem.first == cardID;
                     });

    // A card is in deck
    if (cardIter != m_cards.end())
    {
        if (card.GetMaxAllowedInDeck() < (*cardIter).second + numCardToAdd)
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

bool Deck::DeleteCard(std::string cardID, size_t numCardToDelete)
{
    const auto cardIter =
        std::find_if(m_cards.begin(), m_cards.end(),
                     [&cardID](const std::pair<std::string, size_t>& elem) {
                         return elem.first == cardID;
                     });

    // A card is in deck
    if (cardIter != m_cards.end())
    {
        if ((*cardIter).second - numCardToDelete == 0)
        {
            m_cards.erase(cardIter);
        }

        (*cardIter).second -= numCardToDelete;
        m_numOfCards -= numCardToDelete;

        return true;
    }

    return false;
}
}  // namespace Hearthstonepp