// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

namespace RosettaStone
{
SecretZone::SecretZone(Player* player) : LimitedZone(MAX_SECERT_SIZE)
{
    m_owner = player;
    m_type = ZoneType::SECRET;
}

void SecretZone::Add(Entity& entity, int zonePos)
{
    LimitedZone::Add(entity, zonePos);

    entity.orderOfPlay = entity.owner->GetGame()->GetNextOOP();
}

bool SecretZone::Exist(Entity& entity)
{
    for (auto& secret : m_entities)
    {
        if (entity.card.id == secret->card.id)
        {
            return true;
        }
    }

    return false;
}
}  // namespace RosettaStone
