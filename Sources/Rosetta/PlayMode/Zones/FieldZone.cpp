// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode
{
FieldZone::FieldZone(Player* player)
    : PositioningZone(ZoneType::PLAY, MAX_FIELD_SIZE)
{
    m_game = player->game;
    m_player = player;
}

int FieldZone::GetCountExceptUntouchables() const
{
    return m_count - m_untouchableCount;
}

std::vector<Minion*> FieldZone::GetAll()
{
    return PositioningZone::GetAll();
}

void FieldZone::Add(Playable* entity, int zonePos)
{
    const auto minion = dynamic_cast<Minion*>(entity);

    PositioningZone::Add(minion, zonePos);

    if (minion->player == minion->game->GetCurrentPlayer())
    {
        if (!minion->HasCharge())
        {
            if (minion->HasRush())
            {
                minion->SetAttackableByRush(true);
                minion->game->rushMinions.emplace_back(
                    minion->GetGameTag(GameTag::ENTITY_ID));
            }
            else
            {
                minion->SetExhausted(true);
            }
        }
    }

    minion->orderOfPlay = minion->game->GetNextOOP();

    ActivateAura(minion);

    for (int i = static_cast<int>(adjacentAuras.size()) - 1; i >= 0; --i)
    {
        adjacentAuras[i]->SetIsFieldChanged(true);
    }

    entity->game->triggerManager.OnZoneTrigger(entity);

    if (entity->card->IsUntouchable())
    {
        ++m_untouchableCount;
        m_hasUntouchables = true;
    }
}

Playable* FieldZone::Remove(Playable* entity)
{
    const auto minion = dynamic_cast<Minion*>(entity);

    RemoveAura(minion);

    for (int i = static_cast<int>(adjacentAuras.size()) - 1; i >= 0; --i)
    {
        adjacentAuras[i]->SetIsFieldChanged(true);
    }

    if (entity->card->IsUntouchable() && --m_untouchableCount == 0)
    {
        m_hasUntouchables = false;
    }

    return PositioningZone::Remove(minion);
}

void FieldZone::Replace(Minion* oldEntity, Minion* newEntity)
{
    const int pos = oldEntity->GetZonePosition();

    // Remove old entity
    RemoveAura(oldEntity);

    for (const auto& aura : auras)
    {
        aura->NotifyEntityRemoved(oldEntity);
    }

    if (oldEntity->card->IsUntouchable() && --m_untouchableCount == 0)
    {
        m_hasUntouchables = false;
    }

    oldEntity->SetZonePosition(0);
    oldEntity->player->GetSetasideZone()->Add(oldEntity);

    // Add new entity
    newEntity->orderOfPlay = newEntity->game->GetNextOOP();

    m_entities[pos] = newEntity;
    newEntity->SetZonePosition(pos);
    newEntity->SetZoneType(m_type);
    newEntity->zone = this;

    ActivateAura(newEntity);

    if (newEntity->card->IsUntouchable())
    {
        ++m_untouchableCount;
        m_hasUntouchables = true;
    }

    for (const auto& aura : auras)
    {
        aura->NotifyEntityAdded(newEntity);
    }

    for (const auto& aura : adjacentAuras)
    {
        aura->SetIsFieldChanged(true);
    }

    if (!newEntity->HasCharge())
    {
        if (newEntity->HasRush())
        {
            newEntity->SetAttackableByRush(true);
            newEntity->game->rushMinions.emplace_back(
                newEntity->GetGameTag(GameTag::ENTITY_ID));
        }
        else
        {
            newEntity->SetExhausted(true);
        }
    }
}

void FieldZone::ActivateAura(Minion* entity)
{
    if (entity->card->power.GetTrigger())
    {
        entity->card->power.GetTrigger()->Activate(entity);
    }

    if (entity->card->power.GetAura())
    {
        entity->card->power.GetAura()->Activate(entity);
    }
}

void FieldZone::RemoveAura(const Minion* entity)
{
    if (entity->ongoingEffect)
    {
        entity->ongoingEffect->Remove();
    }
}
}  // namespace RosettaStone::PlayMode
