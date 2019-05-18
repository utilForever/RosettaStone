// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Zones/DeckZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone
{
DeckZone::DeckZone()
{
    m_cards.fill(nullptr);
}

Player& DeckZone::GetOwner() const
{
    return *m_owner;
}

void DeckZone::SetOwner(Player& owner)
{
    m_owner = &owner;
}

bool DeckZone::IsEmpty() const
{
    return GetNumOfCards() == 0;
}

std::size_t DeckZone::GetNumOfCards() const
{
    return m_numCard;
}

Entity* DeckZone::GetTopCard() const
{
    if (IsEmpty())
    {
        return nullptr;
    }

    return m_cards[m_numCard - 1];
}

void DeckZone::AddCard(Entity& card)
{
    m_cards.at(m_numCard) = &card;
    ++m_numCard;
}

Entity& DeckZone::RemoveCard(Entity& card)
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

void DeckZone::Shuffle()
{
    Random::shuffle(m_cards.begin(), m_cards.begin() + m_numCard);
}
}  // namespace RosettaStone
