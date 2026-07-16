// Copyright (c) 2017-2026 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Models/Player.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Player] - Game tags share entity storage")
{
    Player player;
    player.SetGameTag(GameTag::TIMEOUT, 30);

    CHECK_EQ(player.GetNativeGameTag(GameTag::TIMEOUT), 30);
}
