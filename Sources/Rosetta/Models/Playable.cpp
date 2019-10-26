// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Playable.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
Playable::Playable(Player* _player, Card* _card, std::map<GameTag, int> _tags)
    : Entity(_player->game, _card, _tags)
{
    player = _player;
}
}  // namespace RosettaStone
