// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Zones/HandZone.hpp>

namespace RosettaStone
{
HandZone::HandZone(Player* player) : PositioningZone(MAX_HAND_SIZE)
{
    m_owner = player;
    m_type = ZoneType::HAND;
}

void HandZone::Add(Entity& entity, int zonePos)
{
    PositioningZone::Add(entity, zonePos);

    if (entity.card.power.GetTrigger().has_value())
    {
        entity.card.power.GetTrigger().value().Activate(entity);
    }
}

Entity& HandZone::Remove(Entity& entity)
{
    for (auto* enchant : entity.appliedEnchantments)
    {
        if (enchant->activatedTrigger != nullptr)
        {
            enchant->activatedTrigger->Remove();
        }
    }

    return PositioningZone::Remove(entity);
}
}  // namespace RosettaStone
