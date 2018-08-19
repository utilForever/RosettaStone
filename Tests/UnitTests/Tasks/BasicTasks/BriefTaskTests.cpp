#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <Tasks/BasicTasks/BriefTask.h>

using namespace Hearthstonepp;

TEST(BriefTask, GetTaskID)
{
    BasicTasks::BriefTask brief;
    EXPECT_EQ(brief.GetTaskID(), +TaskID::BRIEF);
}

TEST(BriefTask, Run)
{
    BasicTasks::BriefTask brief;
    TestUtils::GenPlayer gen(CardClass::DRUID, CardClass::ROGUE);

    gen.player1.id = 100;

    MetaData result = brief.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::BRIEF);

    TaskMeta meta;
    result = brief.Run(gen.player1, gen.player2, meta);
    EXPECT_EQ(result, MetaData::BRIEF);
    EXPECT_EQ(meta.id, +TaskID::BRIEF);
    EXPECT_EQ(meta.status, MetaData::BRIEF);
    EXPECT_EQ(meta.userID, gen.player1.id);
}