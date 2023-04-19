// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathNumberIndexTask.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;
using namespace TestUtils;

TEST_CASE("[MathNumberIndexTask] - Run_Add")
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

    game.taskStack.num[0] = 1;
    game.taskStack.num[1] = 2;

    MathNumberIndexTask task(0, 1, MathOperation::ADD, 1);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(game.taskStack.num[1], 3);
}

TEST_CASE("[MathNumberIndexTask] - Run_Sub")
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

    game.taskStack.num[2] = 5;
    game.taskStack.num[3] = 3;

    MathNumberIndexTask task(2, 3, MathOperation::SUB, 2);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(game.taskStack.num[2], 2);
}

TEST_CASE("[MathNumberIndexTask] - Run_Mul")
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

    game.taskStack.num[4] = 2;
    game.taskStack.num[0] = 4;

    MathNumberIndexTask task(4, 0, MathOperation::MUL, 3);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(game.taskStack.num[3], 8);
}

TEST_CASE("[MathNumberIndexTask] - Run_Div")
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

    game.taskStack.num[1] = 9;
    game.taskStack.num[2] = 3;

    MathNumberIndexTask task(1, 2, MathOperation::DIV, 4);
    task.SetPlayer(player1);

    TaskStatus result = task.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(game.taskStack.num[4], 3);
}