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
DeckZone::DeckZone(Player* player) : LimitedZone(MAX_DECK_SIZE)
{
    m_owner = player;
    m_type = ZoneType::DECK;
}

Entity* DeckZone::GetTopCard() const
{
    return m_entities[m_count - 1];
}

void DeckZone::Add(Entity& entity, int zonePos)
{
    LimitedZone::Add(entity, zonePos);

    if (entity.card->power.GetTrigger())
    {
        entity.card->power.GetTrigger()->Activate(&entity,
                                                 TriggerActivation::DECK);
    }
}

void DeckZone::Shuffle()
{
    Random::shuffle(m_entities.begin(), m_entities.begin() + m_count);
}
}  // namespace RosettaStone
