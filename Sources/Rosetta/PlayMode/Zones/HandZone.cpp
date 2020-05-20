// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Auras/SummoningPortalAura.hpp>
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

void HandZone::RefCopy(HandZone* rhs) const
{
    for (int i = 0; i < m_count; ++i)
    {
        delete m_entities[i];
    }

    for (int i = 0; i < rhs->m_count; ++i)
    {
        m_entities[i] = rhs->m_entities[i];
    }
}

void HandZone::Add(Playable* entity, int zonePos)
{
    PositioningZone::Add(entity, zonePos);

    if (const auto aura = entity->card->power.GetAura(); aura)
    {
        if (auto effect = dynamic_cast<AdaptiveCostEffect*>(aura); effect)
        {
            effect->Activate(entity);
        }
    }

    if (auto trigger = entity->card->power.GetTrigger(); trigger)
    {
        trigger->Activate(entity, TriggerActivation::HAND);
    }

    for (auto& iAura : entity->game->auras)
    {
        if (auto aura = dynamic_cast<Aura*>(iAura);
            aura && aura->GetType() == AuraType::HAND)
        {
            aura->Apply(entity);
        }
    }

    entity->game->triggerManager.OnZoneTrigger(entity);
}

Playable* HandZone::Remove(Playable* entity)
{
    entity->ResetCost();

    for (const auto& enchant : entity->appliedEnchantments)
    {
        if (enchant->activatedTrigger != nullptr)
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

    for (int i = 0; i < m_count; ++i)
    {
        entities[i] = m_entities[i];
    }

    delete[] m_entities;
    m_entities = entities;
    m_maxSize = newSize;
}

int HandZone::FindIndex(Entity* entity) const
{
    for (std::size_t idx = 0; idx < MAX_HAND_SIZE; ++idx)
    {
        if (m_entities[idx] == entity)
        {
            return idx;
        }
    }

    return -1;
}
}  // namespace RosettaStone::PlayMode
