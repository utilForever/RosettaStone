// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(ControlTask, GetTaskID)
{
    const ControlTask control(EntityType::TARGET);
    EXPECT_EQ(control.GetTaskID(), TaskID::CONTROL);
}

TEST(ControlTask, Run)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    std::vector<Card> cards;
    cards.reserve(5);

    const std::string name = "test";
    for (std::size_t i = 0; i < 6; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player1, cards[i]);
        PlayMinionCard(player2, cards[i]);
    }

    ControlTask control(EntityType::TARGET);
    control.SetTarget(player2Field.GetMinion(0));
    TaskStatus result = control.Run(player1);

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(player1Field.GetNumOfMinions(), 7u);
    EXPECT_EQ(player2Field.GetNumOfMinions(), 5u);

    // Check controlled minion has valid data
    EXPECT_EQ(player1Field.GetMinion(6)->GetAttack(), 1);
    EXPECT_EQ(player1Field.GetMinion(6)->GetHealth(), 1);

    control.SetTarget(player2Field.GetMinion(1));
    result = control.Run(player1);

    EXPECT_EQ(result, TaskStatus::STOP);
    EXPECT_EQ(player1Field.GetNumOfMinions(), 7u);
    EXPECT_EQ(player2Field.GetNumOfMinions(), 5u);
}
