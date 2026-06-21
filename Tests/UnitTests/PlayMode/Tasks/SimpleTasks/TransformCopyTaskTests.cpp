// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformCopyTask.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;

TEST_CASE("[TransformCopyTask] - Invalid source stops")
{
    TransformCopyTask task;

    CHECK_EQ(task.Run(), TaskStatus::STOP);
}
