// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetEventNumberTask.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;
using namespace TestUtils;

TEST_CASE("[GetEventNumberTask] - Run")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    game.currentEventData =
        std::make_unique<EventMetaData>(nullptr, nullptr, 1);

    GetEventNumberTask task0(0);
    task0.SetPlayer(game.GetPlayer1());
    TaskStatus result0 = task0.Run();
    CHECK_EQ(result0, TaskStatus::COMPLETE);
    CHECK_EQ(game.taskStack.num[0], 1);

    GetEventNumberTask task1(1);
    task1.SetPlayer(game.GetPlayer1());
    TaskStatus result1 = task1.Run();
    CHECK_EQ(result1, TaskStatus::COMPLETE);
    CHECK_EQ(game.taskStack.num[1], 1);

    GetEventNumberTask task2(2);
    task2.SetPlayer(game.GetPlayer1());
    CHECK_THROWS_AS(task2.Run(), std::invalid_argument);

    game.currentEventData.reset();
}