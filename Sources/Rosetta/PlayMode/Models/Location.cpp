// Copyright (c) 2017-2021 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Location::Location(Player* _player, Card* _card, std::map<GameTag, int> tags,
                   int id)
    : Playable(_player, _card, std::move(tags), id)
{
    // Do nothing
}
}  // namespace RosettaStone::PlayMode
