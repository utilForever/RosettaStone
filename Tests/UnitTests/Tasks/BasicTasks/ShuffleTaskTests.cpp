// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/BasicTasks/ShuffleTask.h>

using namespace Hearthstonepp;

TEST(ShuffleTask, GetTaskID)
{
    const BasicTasks::ShuffleTask init;
    EXPECT_EQ(init.GetTaskID(), +TaskID::SHUFFLE);
}

TEST(ShuffleTask, Run)
{
    BasicTasks::ShuffleTask init;
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, 1);

    for (int i = 0; i < 5; i++)
    {
        auto card = TestUtils::GenerateMinionCard("minion", 5, 1);
        agent.GetPlayer1().cards.emplace_back(new Minion(card));
    }

    MetaData result = init.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::SHUFFLE_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().cards.size(), static_cast<size_t>(5));
}
