// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Cards/Minion.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Tasks/SimpleTasks/ControlTask.hpp>

using namespace Hearthstonepp;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(ControlTask, GetTaskID)
{
    const ControlTask control(EntityType::TARGET);
    EXPECT_EQ(control.GetTaskID(), +TaskID::CONTROL);
}
