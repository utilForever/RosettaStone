// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Zones/DeckZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone
{
DeckZone::DeckZone(Player* player) : LimitedZone(ZoneType::DECK, MAX_DECK_SIZE)
{
    m_game = player->game;
    m_player = player;
}

void DeckZone::RefCopy(DeckZone* rhs) const
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

Playable* DeckZone::GetTopCard() const
{
    return m_entities[m_count - 1];
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
}  // namespace RosettaStone
