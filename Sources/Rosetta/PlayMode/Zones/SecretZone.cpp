// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

namespace RosettaStone::PlayMode
{
SecretZone::SecretZone(Player* player)
    : LimitedZone(ZoneType::SECRET, MAX_SECERT_SIZE)
{
    m_game = player->game;
    m_player = player;
}

void SecretZone::RefCopy(SecretZone* rhs) const
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

void SecretZone::Add(Playable* entity, int zonePos)
{
    const auto spell = dynamic_cast<Spell*>(entity);

    if (spell->IsQuest())
    {
        if (quest != nullptr)
        {
            throw std::logic_error("Another quest is already in play");
        }

        quest = spell;
    }

    LimitedZone::Add(spell, zonePos);

    entity->orderOfPlay = entity->game->GetNextOOP();
}

Playable* SecretZone::Remove(Playable* entity)
{
    return LimitedZone::Remove(dynamic_cast<Spell*>(entity));
}

void SecretZone::ChangeEntity([[maybe_unused]] Playable* oldEntity,
                              [[maybe_unused]] Playable* newEntity)
{
    throw std::logic_error("SecretZone::ChangeEntity() - Not implemented!");
}

bool SecretZone::Exist(Playable* entity) const
{
    for (int i = 0; i < m_count; ++i)
    {
        if (entity->card->id == m_entities[i]->card->id)
        {
            return true;
        }
    }

    return false;
}
}  // namespace RosettaStone::PlayMode
