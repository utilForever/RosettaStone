// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Deck.hpp>

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
}  // namespace Hearthstonepp