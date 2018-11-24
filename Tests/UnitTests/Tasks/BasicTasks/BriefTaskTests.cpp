// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/BasicTasks/BriefTask.h>

using namespace Hearthstonepp;
using namespace BasicTasks;

TEST(BriefTask, GetTaskID)
{
    const BriefTask brief;
    EXPECT_EQ(brief.GetTaskID(), +TaskID::BRIEF);
}

TEST(BriefTask, Run)
{
    BriefTask brief;
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    agent.GetPlayer1().id = 100;

    MetaData result = brief.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::BRIEF);

    TaskMeta meta;
    result = brief.Run(agent.GetPlayer1(), meta);
    EXPECT_EQ(result, MetaData::BRIEF);
    EXPECT_EQ(meta.id, +TaskID::BRIEF);
    EXPECT_EQ(meta.status, MetaData::BRIEF);
    EXPECT_EQ(meta.userID, agent.GetPlayer1().id);
}
