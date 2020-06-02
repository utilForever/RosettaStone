// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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
}  // namespace RosettaStone::Battlegrounds
