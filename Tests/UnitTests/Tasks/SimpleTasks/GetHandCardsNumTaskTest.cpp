// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetHandCardsNumTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(GetHandCardsNumTask, GetTaskID)
{
    const GetHandCardsNumTask getHandCardsNum(EntityType::HAND);
    EXPECT_EQ(getHandCardsNum.GetTaskID(), TaskID::GET_HAND_CARDS_NUM);
}

TEST(GetHandCardsNumTask, Run)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    const std::string name = "test";
    
    std::vector<Card> cards;
    cards.reserve(5);
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player1, cards[i]);
    }

    std::vector<Card> opcards;
    opcards.reserve(4);
    for (std::size_t i = 0; i < 3; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        opcards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player2, opcards[i]);
    }

    GetHandCardsNumTask task1(EntityType::HAND);
    TaskStatus result1 = task1.Run(player1);
    EXPECT_EQ(result1, TaskStatus::COMPLETE);
    EXPECT_EQ((int)player1.GetHand().GetNumOfCards(), player1.GetGame()->taskStack.num);

    GetHandCardsNumTask task2(EntityType::ENEMY_HAND);
    TaskStatus result2 = task2.Run(player1);
    EXPECT_EQ(result2, TaskStatus::COMPLETE);
    EXPECT_EQ((int)player1.opponent->GetHand().GetNumOfCards(), player1.GetGame()->taskStack.num);
}

