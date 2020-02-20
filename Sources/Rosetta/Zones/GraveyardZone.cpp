// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>

namespace RosettaStone
{
GraveyardZone::GraveyardZone(Player* player)
    : UnlimitedZone(player, ZoneType::GRAVEYARD)
{
    // Do nothing
}

void GraveyardZone::RefCopy(const GraveyardZone& rhs)
{
    for (int i = 0; i < GetCount(); ++i)
    {
        delete m_entities[i];
    }

    for (int i = 0; i < rhs.GetCount(); ++i)
    {
        m_entities.emplace_back(rhs.m_entities[i]);
    }
}

void GraveyardZone::Add(Playable* entity, int zonePos)
{
    UnlimitedZone::Add(entity, zonePos);

    const int enchantSize =
        static_cast<int>(entity->appliedEnchantments.size());
    for (int i = enchantSize - 1; i >= 0; --i)
    {
        entity->appliedEnchantments[i]->Remove();
    }
}
}  // namespace RosettaStone
