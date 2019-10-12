// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Commons/Utils.hpp>

#include <random>

TEST(Base64, Decode)
{
    auto decoded = DecodeBase64("AQIDBA==");

    EXPECT_EQ(decoded.size(), 4u);
    EXPECT_EQ(decoded[0], 1);
    EXPECT_EQ(decoded[1], 2);
    EXPECT_EQ(decoded[2], 3);
    EXPECT_EQ(decoded[3], 4);
}