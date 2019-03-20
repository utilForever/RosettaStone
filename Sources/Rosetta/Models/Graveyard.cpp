// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Commons/Constants.hpp>
#include <hspp/Models/Graveyard.hpp>

namespace Hearthstonepp
{
Graveyard::Graveyard()
{
    m_cards.reserve(START_DECK_SIZE);
}

Player& Graveyard::GetOwner() const
{
    return *m_owner;
}

void Graveyard::SetOwner(Player& owner)
{
    m_owner = &owner;
}

void Graveyard::AddCard(Entity& card)
{
    m_cards.emplace_back(&card);
}
}  // namespace Hearthstonepp