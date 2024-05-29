// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Zones/HandZone.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds
{
CardData& HandZone::operator[](int zonePos)
{
    return m_cards.at(zonePos).value();
}

void HandZone::Add(CardData card, int zonePos)
{
    if (zonePos > m_count)
    {
        throw std::invalid_argument("Zone position isn't in a valid range.");
    }

    const int pos = zonePos < 0 ? m_count : zonePos;

    if (IsFull())
    {
        return;
    }

    if (pos < 0 || pos == m_count)
    {
        m_cards[m_count] = card;
    }
    else
    {
        for (int i = m_count - 1; i >= pos; --i)
        {
            m_cards[i + 1] = m_cards[i];
        }

        m_cards[pos] = card;
    }

    ++m_count;

    std::visit([&](auto&& _card) { return _card.SetZoneType(m_type); },
               m_cards[pos].value());

    Reposition(pos);
}

const CardData HandZone::Remove(CardData& card)
{
    const ZoneType cardZone = std::visit(
        [&](auto&& _card) -> ZoneType { return _card.GetZoneType(); }, card);
    if (cardZone != m_type)
    {
        throw std::logic_error("Couldn't remove entity from zone.");
    }

    const int cardPos = std::visit(
        [&](auto&& _card) -> int { return _card.GetZonePosition(); }, card);
    int count = m_count;

    CardData result = m_cards.at(cardPos).value();

    if (cardPos < --count)
    {
        for (int i = cardPos + 1; i < MAX_HAND_SIZE; ++i)
        {
            m_cards[i - 1] = m_cards[i];
        }

        m_cards[MAX_HAND_SIZE - 1] = std::nullopt;
    }

    m_count = count;

    Reposition(cardPos);

    return result;
}

void HandZone::Reposition(int zonePos)
{
    if (zonePos < 0)
    {
        std::visit(
            [&](auto&& _card) { return _card.SetZonePosition(m_count - 1); },
            m_cards[m_count - 1].value());
        return;
    }

    for (int i = m_count - 1; i >= zonePos; --i)
    {
        std::visit([&](auto&& _card) { return _card.SetZonePosition(i); },
                   m_cards[i].value());
    }
}

int HandZone::GetCount() const
{
    return m_count;
}

bool HandZone::IsFull() const
{
    return m_count == MAX_HAND_SIZE;
}
}  // namespace RosettaStone::Battlegrounds
