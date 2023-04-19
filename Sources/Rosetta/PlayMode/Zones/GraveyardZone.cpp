// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

namespace RosettaStone::PlayMode
{
GraveyardZone::GraveyardZone(Player* player)
    : UnlimitedZone(player, ZoneType::GRAVEYARD)
{
    // Do nothing
}

void GraveyardZone::Add(Playable* entity, int zonePos)
{
    UnlimitedZone::Add(entity, zonePos);

    const auto enchantments = entity->appliedEnchantments;
    if (enchantments.empty())
    {
        return;
    }

    const int enchantSize = static_cast<int>(enchantments.size());
    for (int i = enchantSize - 1; i >= 0; --i)
    {
        enchantments[i]->Remove();
    }
}
}  // namespace RosettaStone::PlayMode
