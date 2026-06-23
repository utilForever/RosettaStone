// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Utils.hpp>

TEST_CASE("[Base64] - Decode")
{
    auto decoded1 = DecodeBase64("AQIDBA==");
    CHECK_EQ(decoded1.size(), 4u);
    CHECK_EQ(decoded1[0], 1);
    CHECK_EQ(decoded1[1], 2);
    CHECK_EQ(decoded1[2], 3);
    CHECK_EQ(decoded1[3], 4);

    auto decoded2 = DecodeBase64("!");
    CHECK(decoded2.empty());
}
