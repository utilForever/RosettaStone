// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Deck.hpp>

#include <algorithm>
#include <random>

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

void Deck::AddCard(Entity& card)
{
    m_cards.at(m_numCard) = &card;
    ++m_numCard;
}

void Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(m_cards.begin(), m_cards.end(), gen);
}
}  // namespace Hearthstonepp