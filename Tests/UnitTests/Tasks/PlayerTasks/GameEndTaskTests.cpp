// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Game/Game.hpp>
#include <hspp/Tasks/PlayerTasks/GameEndTask.hpp>

using namespace Hearthstonepp;
using namespace PlayerTasks;

TEST(GameEndTask, GetTaskID)
{
    const GameEndTask gameEnd;
    EXPECT_EQ(gameEnd.GetTaskID(), +TaskID::GAME_END);
}

TEST(GameEndTask, Run)
{
    GameEndTask gameEnd;
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    game.GetPlayer1().SetID(100);

    MetaData result = gameEnd.Run(game.GetPlayer1());
    EXPECT_EQ(result, MetaData::GAME_END);
}
