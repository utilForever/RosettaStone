// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

namespace RosettaStone
{
FieldZone::FieldZone(Player* player) : PositioningZone(MAX_FIELD_SIZE)
{
    m_owner = player;
    m_type = ZoneType::PLAY;
}

std::vector<Minion*> FieldZone::GetAll()
{
    return PositioningZone::GetAll();
}

void FieldZone::Add(Entity& entity, int zonePos)
{
    PositioningZone::Add(entity, zonePos);

    if (entity.GetGameTag(GameTag::CHARGE) != 1)
    {
        entity.SetExhausted(true);
    }

    for (auto& aura : auras)
    {
        aura->SetToBeUpdated(true);
    }

    entity.orderOfPlay = entity.owner->GetGame()->GetNextOOP();

    ActivateAura(entity);
}

Entity& FieldZone::Remove(Entity& entity)
{
    RemoveAura(entity);

    return PositioningZone::Remove(entity);
}

void FieldZone::Replace(Entity& oldEntity, Entity& newEntity)
{
    const int pos = oldEntity.GetZonePosition();
    m_entities[pos] = dynamic_cast<Minion*>(&newEntity);
    newEntity.SetZonePosition(pos);
    newEntity.SetZoneType(m_type);
    newEntity.zone = this;

    // Remove old entity
    RemoveAura(oldEntity);
    for (auto& aura : auras)
    {
        aura->RemoveEntity(&oldEntity);
    }

    // Add new entity
    newEntity.orderOfPlay = newEntity.owner->GetGame()->GetNextOOP();
    ActivateAura(newEntity);
    for (auto& aura : auras)
    {
        aura->SetToBeUpdated(true);
    }

    // Set exhausted by checking GameTag::CHARGE
    if (newEntity.GetGameTag(GameTag::CHARGE) == 0)
    {
        newEntity.SetExhausted(true);
    }
}

void FieldZone::ActivateAura(Entity& entity)
{
    if (entity.card->power.GetTrigger())
    {
        entity.card->power.GetTrigger()->Activate(&entity);
    }

    if (entity.card->power.GetAura())
    {
        entity.card->power.GetAura()->Activate(&entity);
    }

    const int spellPower = entity.GetGameTag(GameTag::SPELLPOWER);
    if (spellPower > 0)
    {
        entity.owner->currentSpellPower += spellPower;
    }
}

void FieldZone::RemoveAura(Entity& entity)
{
    if (entity.onGoingEffect != nullptr)
    {
        entity.onGoingEffect->Remove();
    }

    const int spellPower = entity.GetGameTag(GameTag::SPELLPOWER);
    if (entity.owner->currentSpellPower > 0 && spellPower > 0)
    {
        entity.owner->currentSpellPower -= spellPower;
    }
}
}  // namespace RosettaStone
