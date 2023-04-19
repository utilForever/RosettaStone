// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Spell.hpp>

#include <utility>

namespace RosettaStone::Battlegrounds
{
Spell::Spell(Card card) : m_card(std::move(card))
{
    // Do nothing
}

ZoneType Spell::GetZoneType() const
{
    return m_zoneType;
}

void Spell::SetZoneType(ZoneType type)
{
    m_zoneType = type;
}

int Spell::GetZonePosition() const
{
    return m_zonePos;
}

void Spell::SetZonePosition(int pos)
{
    m_zonePos = pos;
}
}  // namespace RosettaStone::Battlegrounds
