// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Models/Game.hpp>
#include <hspp/Tasks/SimpleTasks/DamageTask.hpp>

using namespace Hearthstonepp;
using namespace SimpleTasks;
using namespace TestUtils;

TEST(DamageTask, GetTaskID)
{
    const DamageTask damage(EntityType::ENEMIES, 2);
    EXPECT_EQ(damage.GetTaskID(), +TaskID::DAMAGE);
}

TEST(DamageTask, Run)
{
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);
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

    EXPECT_EQ(result, TaskStatus::DAMAGE_SUCCESS);
    EXPECT_EQ(player1.GetField().GetNumOfMinions(), 0u);
}
