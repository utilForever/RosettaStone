// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Deck.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace Hearthstonepp
{
Deck::Deck()
{
    m_cards.fill(nullptr);
}

Player& Deck::GetOwner() const
{
    return *m_owner;
}

void Deck::SetOwner(Player& owner)
{
    m_owner = &owner;
}

bool Deck::IsEmpty() const
{
    return GetNumOfCards() == 0;
}

std::size_t Deck::GetNumOfCards() const
{
    return m_numCard;
}

Entity* Deck::GetTopCard() const
{
    if (IsEmpty())
    {
        return nullptr;
    }

    return m_cards[m_numCard - 1];
}

void Deck::AddCard(Entity& card)
{
    m_cards.at(m_numCard) = &card;
    ++m_numCard;
}

Entity& Deck::RemoveCard(Entity& card)
{
    std::size_t idx = 0;

    for (; idx < m_numCard; ++idx)
    {
        if (m_cards[idx] == &card)
        {
            m_cards[idx] = nullptr;
            break;
        }
    }

    for (; idx < m_numCard - 1; ++idx)
    {
        m_cards[idx] = m_cards[idx + 1];
        m_cards[idx + 1] = nullptr;
    }

    --m_numCard;

    return card;
}

void Deck::Shuffle()
{
    Random::shuffle(m_cards.begin(), m_cards.begin() + m_numCard);
}
}  // namespace Hearthstonepp