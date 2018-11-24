// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/BasicTasks/GameEndTask.h>

using namespace Hearthstonepp;
using namespace BasicTasks;

TEST(GameEndTask, GetTaskID)
{
    const GameEndTask gameEnd;
    EXPECT_EQ(gameEnd.GetTaskID(), +TaskID::GAME_END);
}

TEST(GameEndTask, Run)
{
    GameEndTask gameEnd;
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    agent.GetPlayer1().id = 100;

    MetaData result = gameEnd.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::GAME_END);

    TaskMeta meta;
    result = gameEnd.Run(agent.GetPlayer1(), meta);
    EXPECT_EQ(result, MetaData::GAME_END);
    EXPECT_EQ(meta.id, +TaskID::GAME_END);
    EXPECT_EQ(meta.status, MetaData::GAME_END);
    EXPECT_EQ(meta.userID, agent.GetPlayer1().id);
}
