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

    for (const auto& player : game.GetGameState().players)
    {
        CHECK_EQ(player.heroChoices.size(), 4u);
    }
}