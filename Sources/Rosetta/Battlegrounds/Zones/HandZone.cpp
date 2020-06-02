// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Zones/HandZone.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds
{
void HandZone::Add(std::variant<Minion, Spell> card, int zonePos)
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

    std::visit([&](auto&& _card) { return _card.SetZoneType(m_type); }, card);
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
