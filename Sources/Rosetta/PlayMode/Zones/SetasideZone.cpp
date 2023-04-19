// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode
{
SetasideZone::SetasideZone(Player* player)
    : UnlimitedZone(player, ZoneType::SETASIDE)
{
    // Do nothing
}

Playable* SetasideZone::GetEntity(int id) const
{
    for (auto& entity : m_entities)
    {
        if (entity->GetGameTag(GameTag::ENTITY_ID) == id)
        {
            return entity;
        }
    }

    return nullptr;
}
}  // namespace RosettaStone::PlayMode
