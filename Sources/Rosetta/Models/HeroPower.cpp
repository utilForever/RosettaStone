// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/HeroPower.hpp>

#include <utility>

namespace RosettaStone
{
HeroPower::HeroPower(Player& _owner, Card* _card, std::map<GameTag, int> tags)
    : Entity(_owner, _card, std::move(tags))
{
    // Do nothing
}
}  // namespace RosettaStone
