// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Tasks/SimpleTasks/DrawOpTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

TEST(DrawOpTask, GetTaskID)
{
    const DrawOpTask drawOp(1);
    EXPECT_EQ(drawOp.GetTaskID(), +TaskID::DRAWOP);
}
