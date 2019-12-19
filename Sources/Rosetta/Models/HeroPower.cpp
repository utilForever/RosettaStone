// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Character.hpp>
#include <Rosetta/Models/HeroPower.hpp>

#include <utility>

namespace RosettaStone
{
HeroPower::HeroPower(Player* player, Card* card, std::map<GameTag, int> tags)
    : Playable(player, card, std::move(tags))
{
    // Do nothing
}

bool HeroPower::TargetingRequirements(Character* target) const
{
    return !target->GetGameTag(GameTag::CANT_BE_TARGETED_BY_HERO_POWERS) &&
           Playable::TargetingRequirements(target);
}
}  // namespace RosettaStone
