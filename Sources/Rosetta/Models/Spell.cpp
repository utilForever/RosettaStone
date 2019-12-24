// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

#include <utility>

namespace RosettaStone
{
Spell::Spell(Player* player, Card* card, std::map<GameTag, int> tags, int id)
    : Playable(player, card, std::move(tags), id)
{
    // Do nothing
}

bool Spell::IsSecret() const
{
    return GetGameTag(GameTag::SECRET) == 1;
}

bool Spell::IsCountered() const
{
    return GetGameTag(GameTag::CANT_PLAY) == 1;
}

bool Spell::TargetingRequirements(Character* target) const
{
    return !target->GetGameTag(GameTag::CANT_BE_TARGETED_BY_SPELLS) &&
           Playable::TargetingRequirements(target);
}

bool Spell::IsPlayableByPlayer()
{
    if (IsSecret() && (player->GetSecretZone()->IsFull() ||
                       player->GetSecretZone()->Exist(this)))
    {
        return false;
    }

    return Playable::IsPlayableByPlayer();
}
}  // namespace RosettaStone
