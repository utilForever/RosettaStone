// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode
{
DeckZone::DeckZone(Player* player) : LimitedZone(ZoneType::DECK, MAX_DECK_SIZE)
{
    m_game = player->game;
    m_player = player;
}

Playable* DeckZone::GetTopCard() const
{
    if (IsEmpty())
    {
        return nullptr;
    }

    return m_entities[m_count - 1];
}

Playable* DeckZone::GetNthTopCard(int rank) const
{
    if (IsEmpty() || rank < 0 || rank > m_count)
    {
        return nullptr;
    }

    return m_entities[m_count - rank];
}

Playable* DeckZone::GetBottomCard() const
{
    if (IsEmpty())
    {
        return nullptr;
    }

    return m_entities[0];
}

Playable* DeckZone::GetNthBottomCard(int rank) const
{
    if (IsEmpty() || rank < 0 || rank > m_count)
    {
        return nullptr;
    }

    return m_entities[rank - 1];
}

void DeckZone::Add(Playable* entity, int zonePos)
{
    LimitedZone::Add(entity, zonePos);

    if (entity->card->power.GetTrigger())
    {
        entity->card->power.GetTrigger()->Activate(entity,
                                                   TriggerActivation::DECK);
    }
}

void DeckZone::ChangeEntity(Playable* oldEntity, Playable* newEntity)
{
    bool flag = false;
    for (int i = 0; i < m_count; ++i)
    {
        if (m_entities[i] == oldEntity)
        {
            m_entities[i] = newEntity;
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        throw std::logic_error(
            "DeckZone::ChangeEntity() - Can't find old entity");
    }

    newEntity->zone = this;
}

void DeckZone::Shuffle() const
{
    Random::shuffle(m_entities, m_entities + m_count);
}

void DeckZone::SetEntity(int index, Playable* newEntity)
{
    m_entities[index] = newEntity;
    newEntity->zone = this;
}

void DeckZone::Swap(const Playable* entity1, const Playable* entity2) const
{
    if (entity1->zone->GetType() != entity2->zone->GetType())
    {
        throw std::logic_error("Swap not possible because of zone mismatch");
    }

    int entity1Pos = -1, entity2Pos = -1;
    for (int i = 0; i < m_count; ++i)
    {
        if (m_entities[i] == entity1)
        {
            entity1Pos = i;
        }

        if (m_entities[i] == entity2)
        {
            entity2Pos = i;
        }
    }

    if (entity1Pos == -1 || entity2Pos == -1 || entity1Pos == entity2Pos)
    {
        return;
    }

    const auto temp = m_entities[entity1Pos];
    m_entities[entity1Pos] = m_entities[entity2Pos];
    m_entities[entity2Pos] = temp;
}
}  // namespace RosettaStone::PlayMode
