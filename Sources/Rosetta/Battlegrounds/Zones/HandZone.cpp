// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Zones/HandZone.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds
{
void HandZone::Add(const std::variant<Minion, Spell>& card, int zonePos)
{
    if (zonePos > m_count)
    {
        throw std::invalid_argument("Zone position isn't in a valid range.");
    }

    if (IsFull())
    {
        return;
    }

    if (zonePos < 0 || zonePos == m_count)
    {
        m_cards[m_count] = card;
    }
    else
    {
        for (int i = m_count - 1; i >= zonePos; --i)
        {
            m_cards[i + 1] = m_cards[i];
        }

        m_cards[zonePos] = card;
    }

    ++m_count;
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
