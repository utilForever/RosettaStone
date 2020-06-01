// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Zones/FieldZone.hpp>

#include <stdexcept>

namespace RosettaStone::Battlegrounds
{
Minion& FieldZone::operator[](int zonePos)
{
    return m_minions.at(zonePos).value();
}

void FieldZone::Add(const Minion& minion, int zonePos)
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
        m_minions[m_count] = minion;
    }
    else
    {
        for (int i = m_count - 1; i >= zonePos; --i)
        {
            m_minions[i + 1] = m_minions[i];
        }

        m_minions[zonePos] = minion;
    }

    ++m_count;
}

bool FieldZone::IsFull() const
{
    return m_count == MAX_FIELD_SIZE;
}
}  // namespace RosettaStone::Battlegrounds
