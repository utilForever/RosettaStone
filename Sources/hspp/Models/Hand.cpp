// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Hand.hpp>

namespace Hearthstonepp
{
Hand::Hand()
{
    m_cards.fill(nullptr);
}

Player& Hand::GetOwner() const
{
    return *m_owner;
}

void Hand::SetOwner(Player& owner)
{
    m_owner = &owner;
}

std::size_t Hand::GetNumOfCards() const
{
    std::size_t ret = 0;

    for (auto& card : m_cards)
    {
        if (card != nullptr)
        {
            ++ret;
        }
    }

    return ret;
}

void Hand::AddCard(Entity& card)
{
    m_cards.at(m_numCard) = &card;
    ++m_numCard;
}
}  // namespace Hearthstonepp