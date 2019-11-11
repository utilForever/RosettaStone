// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Zones/SetasideZone.hpp>

namespace RosettaStone
{
SetasideZone::SetasideZone(Player* player)
    : UnlimitedZone(player, ZoneType::SETASIDE)
{
    // Do nothing
}

Playable* SetasideZone::GetEntity(int id)
{
    for (auto& entity : m_entities)
    {
        if (entity->id == id)
        {
            return entity;
        }
    }

    return nullptr;
}
}  // namespace RosettaStone
