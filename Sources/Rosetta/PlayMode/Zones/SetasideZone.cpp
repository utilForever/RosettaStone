// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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

void SetasideZone::RefCopy(SetasideZone* rhs)
{
    for (int i = 0; i < GetCount(); ++i)
    {
        delete m_entities[i];
    }

    for (int i = 0; i < rhs->GetCount(); ++i)
    {
        m_entities.emplace_back(rhs->m_entities[i]);
    }
}

Playable* SetasideZone::GetEntity(int id)
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
