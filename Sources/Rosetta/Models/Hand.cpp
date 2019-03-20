// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Hand.hpp>

#include <algorithm>

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

bool Hand::IsFull() const
{
    return GetNumOfCards() == HAND_SIZE;
}

bool Hand::IsEmpty() const
{
    return GetNumOfCards() == 0;
}

std::size_t Hand::GetNumOfCards() const
{
    return m_numCard;
}

Entity* Hand::GetCard(std::size_t pos)
{
    return m_cards.at(pos);
}

std::vector<Entity*> Hand::GetAllCards()
{
    std::vector<Entity*> ret;
    ret.reserve(m_numCard);

    for (size_t i = 0; i < m_numCard; ++i)
    {
        ret.emplace_back(m_cards[i]);
    }

    return ret;
}

std::optional<std::size_t> Hand::FindCardPos(Entity& card)
{
    const auto iter = std::find(m_cards.begin(), m_cards.end(), &card);
    if (iter != std::end(m_cards))
    {
        return std::distance(std::begin(m_cards), iter);
    }

    return std::nullopt;
}

void Hand::AddCard(Entity& card)
{
    m_cards.at(m_numCard) = &card;
    ++m_numCard;
}

void Hand::RemoveCard(Entity& card)
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
}

void Hand::SwapCard(Entity& card1, Entity& card2)
{
    std::size_t card1Pos = FindCardPos(card1).value();
    std::size_t card2Pos = FindCardPos(card2).value();

    std::swap(m_cards[card1Pos], m_cards[card2Pos]);
}
}  // namespace Hearthstonepp