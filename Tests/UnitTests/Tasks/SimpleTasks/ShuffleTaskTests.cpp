// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Cards/Minion.hpp>
#include <hspp/Models/Game.hpp>
#include <hspp/Tasks/SimpleTasks/ShuffleTask.hpp>

using namespace Hearthstonepp;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(ShuffleTask, GetTaskID)
{
    const ShuffleTask init;
    EXPECT_EQ(init.GetTaskID(), +TaskID::SHUFFLE);
}

TEST(ShuffleTask, Run)
{
    ShuffleTask init;
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    for (int i = 0; i < 5; i++)
    {
        auto card = GenerateMinionCard("minion", 5, 1);
        game.GetPlayer1().GetDeck().emplace_back(new Minion(card));
    }

    TaskStatus result = init.Run(game.GetPlayer1());
    EXPECT_EQ(result, TaskStatus::SHUFFLE_SUCCESS);
    EXPECT_EQ(game.GetPlayer1().GetDeck().size(), static_cast<size_t>(5));
}
