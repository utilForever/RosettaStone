// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Models/Character.hpp>
#include <Rosetta/PlayMode/Models/HeroPower.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
HeroPower::HeroPower(Player* _player, Card* _card, std::map<GameTag, int> tags,
                     int id)
    : Playable(_player, _card, std::move(tags), id)
{
    // Do nothing
}

bool HeroPower::TargetingRequirements(Card* _card, Character* target) const
{
    return !target->GetGameTag(GameTag::CANT_BE_TARGETED_BY_HERO_POWERS) &&
           Playable::TargetingRequirements(_card, target);
}
}  // namespace RosettaStone::PlayMode
