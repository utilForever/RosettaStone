// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(DamageTask, GetTaskID)
{
    const DamageTask damage(EntityType::ENEMIES, 2);
    EXPECT_EQ(damage.GetTaskID(), +TaskID::DAMAGE);
}

TEST(DamageTask, Run)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& player1 = game.GetPlayer1();

    std::vector<Card> cards;
    cards.reserve(5);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player1, cards[i]);
    }

    DamageTask damage(EntityType::FRIENDS, 1);
    TaskStatus result = damage.Run(player1);

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(player1.GetField().GetNumOfMinions(), 0u);
}

TEST(DamageTask, SpellPower)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& player1 = game.GetPlayer1();

    std::vector<Card> cards;
    cards.reserve(5);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 5));
        PlayMinionCard(player1, cards[i]);
    }

    DamageTask damage1(EntityType::FRIENDS, 1, true);
    damage1.SetSource(player1.GetField().GetMinion(0));
    TaskStatus result = damage1.Run(player1);

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    for (std::size_t i = 0; i < 5; ++i)
    {
        EXPECT_EQ(player1.GetField().GetMinion(i)->health, 4);
    }

    player1.currentSpellPower = 1;

    DamageTask damage2(EntityType::FRIENDS, 1, true);
    damage2.SetSource(player1.GetField().GetMinion(0));
    result = damage2.Run(player1);

    EXPECT_EQ(result, TaskStatus::COMPLETE);
    for (std::size_t i = 0; i < 5; ++i)
    {
        EXPECT_EQ(player1.GetField().GetMinion(i)->health, 2);
    }
}