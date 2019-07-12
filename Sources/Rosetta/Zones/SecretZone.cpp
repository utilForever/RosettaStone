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

bool SecretZone::Exist(Entity& entity) const
{
    for (int i = 0; i < m_maxSize; ++i)
    {
        if (!m_entities[i])
        {
            continue;
        }

        if (entity.card->id == m_entities[i]->card->id)
        {
            return true;
        }
    }

    return false;
}
}  // namespace RosettaStone
