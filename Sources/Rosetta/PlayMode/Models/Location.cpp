// Copyright (c) 2026 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Location::Location(Player* _player, Card* _card, std::map<GameTag, int> tags,
                   int id)
    : Character(_player, _card, std::move(tags), id)
{
    // Do nothing
}

bool Location::IsOnCooldown() const
{
    return GetGameTag(GameTag::LOCATION_ACTION_COOLDOWN) > 0;
}

void Location::SetOnCooldown(bool onCooldown)
{
    SetGameTag(GameTag::LOCATION_ACTION_COOLDOWN, onCooldown);
    SetExhausted(onCooldown);
}

bool Location::CanAttack() const
{
    return false;
}

void Location::Use()
{
    SetOnCooldown(true);
    SetDamage(GetDamage() + 1);
}

void Location::Destroy()
{
    if (isDestroyed)
    {
        return;
    }

    Playable::Destroy();

    if (zone && GetZoneType() == ZoneType::PLAY)
    {
        zone->Remove(this);
        player->GetGraveyardZone()->Add(this);
    }
}
}  // namespace RosettaStone::PlayMode
