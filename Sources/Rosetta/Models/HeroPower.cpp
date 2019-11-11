// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/HeroPower.hpp>

#include <utility>

namespace RosettaStone
{
HeroPower::HeroPower(Player* player, Card* card, std::map<GameTag, int> tags)
    : Playable(player, card, std::move(tags))
{
    // Do nothing
}
}  // namespace RosettaStone
