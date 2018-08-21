#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <Tasks/BasicTasks/GameEndTask.h>

using namespace Hearthstonepp;

TEST(GameEndTask, GetTaskID)
{
    BasicTasks::GameEndTask gameEnd;
    EXPECT_EQ(gameEnd.GetTaskID(), +TaskID::GAME_END);
}

TEST(GameEndTask, Run)
{
    BasicTasks::GameEndTask gameEnd;
    TestUtils::GenPlayer gen(CardClass::DRUID, CardClass::ROGUE);

    gen.player1.id = 100;

    MetaData result = gameEnd.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::GAME_END);

    TaskMeta meta;
    result = gameEnd.Run(gen.player1, gen.player2, meta);
    EXPECT_EQ(result, MetaData::GAME_END);
    EXPECT_EQ(meta.id, +TaskID::GAME_END);
    EXPECT_EQ(meta.status, MetaData::GAME_END);
    EXPECT_EQ(meta.userID, gen.player1.id);
}
