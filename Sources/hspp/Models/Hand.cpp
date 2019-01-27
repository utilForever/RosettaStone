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

bool Hand::IsEmpty() const
{
    return GetNumOfCards() == 0;
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

Entity* Hand::GetCard(std::size_t pos)
{
    return m_cards.at(pos);
}

std::vector<Entity*> Hand::GetAllCards()
{
    std::vector<Entity*> ret;

    for (auto& card : m_cards)
    {
        if (card != nullptr)
        {
            ret.emplace_back(card);
        }
    }

    return ret;
}

optional<std::size_t> Hand::FindCardPos(Entity& card)
{
    const auto iter = std::find(m_cards.begin(), m_cards.end(), &card);
    if (iter != std::end(m_cards))
    {
        return std::distance(std::begin(m_cards), iter);
    }

    return nullopt;
}

void Hand::AddCard(Entity& card)
{
    m_cards.at(m_numCard) = &card;
    ++m_numCard;
}

void Hand::RemoveCard(Entity& card)
{
    const auto iter = std::find(m_cards.begin(), m_cards.end(), &card);
    if (iter != std::end(m_cards))
    {
        delete *iter;
        *iter = nullptr;
        --m_numCard;
    }
}
}  // namespace Hearthstonepp