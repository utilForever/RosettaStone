// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathNumberIndexTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(MathNumberIndexTask, Run_Add)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player* player1 = game.GetPlayer1();

    game.taskStack.num = 1;
    game.taskStack.num1 = 2;

    MathNumberIndexTask task(0, 1, MathOperation::ADD, 0);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(game.taskStack.num, 3);
}

TEST(MathNumberIndexTask, Run_Sub)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player* player1 = game.GetPlayer1();

    game.taskStack.num = 5;
    game.taskStack.num1 = 3;

    MathNumberIndexTask task(0, 1, MathOperation::SUB, 1);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(game.taskStack.num1, 2);
}

TEST(MathNumberIndexTask, Run_Mul)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player* player1 = game.GetPlayer1();

    game.taskStack.num = 2;
    game.taskStack.num1 = 4;

    MathNumberIndexTask task(0, 1, MathOperation::MUL, 0);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(game.taskStack.num, 8);
}

TEST(MathNumberIndexTask, Run_Div)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player* player1 = game.GetPlayer1();

    game.taskStack.num = 9;
    game.taskStack.num1 = 3;

    MathNumberIndexTask task(0, 1, MathOperation::DIV, 1);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(game.taskStack.num1, 3);
}