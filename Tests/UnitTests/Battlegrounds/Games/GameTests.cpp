// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Games/Game.hpp>

using namespace RosettaStone::Battlegrounds;

TEST_CASE("[Game] - Basic")
{
    Game game;
    game.Start();
}