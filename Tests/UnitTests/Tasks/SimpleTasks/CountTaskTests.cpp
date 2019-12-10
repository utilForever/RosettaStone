// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/CountTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(CountTask, Run)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    CountTask task0(EntityType::HERO, 0);
    task0.SetPlayer(game.GetPlayer1());
    TaskStatus result0 = task0.Run();
    EXPECT_EQ(result0, TaskStatus::COMPLETE);
    EXPECT_EQ(game.taskStack.num[0], 1);

    CountTask task1(EntityType::ENEMY_HERO, 1);
    task1.SetPlayer(game.GetPlayer1());
    TaskStatus result1 = task1.Run();
    EXPECT_EQ(result1, TaskStatus::COMPLETE);
    EXPECT_EQ(game.taskStack.num[1], 1);

    CountTask task2(EntityType::DECK, 2);
    task2.SetPlayer(game.GetPlayer1());
    EXPECT_THROW(task2.Run(), std::invalid_argument);
}