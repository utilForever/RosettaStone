// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

namespace RosettaStone::PlayMode
{
HandZone::HandZone(Player* player)
    : PositioningZone(ZoneType::HAND, MAX_HAND_SIZE)
{
    m_game = player->game;
    m_player = player;
}

void HandZone::Add(Playable* entity, int zonePos)
{
    PositioningZone::Add(entity, zonePos);

    if (const auto aura = entity->card->power.GetAura(); aura)
    {
        if (const auto effect = dynamic_cast<AdaptiveCostEffect*>(aura); effect)
        {
            effect->Activate(entity);
        }
    }

    if (const auto trigger = entity->card->power.GetTrigger(); trigger)
    {
        trigger->Activate(entity, TriggerActivation::HAND);
    }

    entity->game->triggerManager.OnZoneTrigger(entity);
}

Playable* HandZone::Remove(Playable* entity)
{
    entity->ResetCost();

    for (const auto& enchant : entity->appliedEnchantments)
    {
        if (enchant->activatedTrigger)
        {
            enchant->activatedTrigger->Remove();
        }
    }

    if (entity->GetZonePosition() == 0 ||
        entity->GetZonePosition() == m_count - 1)
    {
        entity->SetGameTag(GameTag::LEFT_OR_RIGHT_MOST_CARD_IN_HAND, 1);
    }

    return PositioningZone::Remove(entity);
}

void HandZone::Expand(int newSize)
{
    const auto entities = new Playable*[newSize];

    for (int i = 0; i < std::min(m_count, newSize); ++i)
    {
        entities[i] = m_entities[i];
    }

    delete[] m_entities;
    m_entities = entities;
    m_maxSize = newSize;
}
}  // namespace RosettaStone::PlayMode
