// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Tasks/SimpleTasks/DrawStackTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

TEST(DrawStackTask, GetTaskID)
{
    const DrawStackTask drawStack(1);
    EXPECT_EQ(drawStack.GetTaskID(), TaskID::DRAW_STACK);
}