// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Auras/AdjacentAura.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[AdjacentAura] - Invalid owner throws")
{
    AdjacentAura aura("EX1_162o");

    CHECK_THROWS(aura.Activate(nullptr));
    CHECK_THROWS(aura.Clone(nullptr));
}
