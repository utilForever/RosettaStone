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
