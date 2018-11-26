// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Weapon.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Tasks/BasicTasks/DestroyTask.hpp>

using namespace Hearthstonepp;
using namespace BasicTasks;
using namespace TestUtils;

TEST(DestroyTask, GetTaskID)
{
    const DestroyTask task(EntityType::EMPTY, nullptr, nullptr);
    EXPECT_EQ(task.GetTaskID(), +TaskID::DESTROY);
}

TEST(DestroyTask, Run)
{
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);
    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    auto card = GenerateMinionCard("minion1", 1, 1);

    // Destroy Source Minion
    player1.GetField().emplace_back(new Minion(card));

    DestroyTask task1(EntityType::SOURCE, player1.GetField()[0], nullptr);

    MetaData result = task1.Run(player1);
    EXPECT_EQ(result, MetaData::DESTROY_MINION_SUCCESS);
    EXPECT_EQ(player1.GetField().size(), static_cast<size_t>(0));

    // Destroy Target Minion
    player2.GetField().emplace_back(new Minion(card));

    DestroyTask task2(EntityType::TARGET, nullptr, player2.GetField()[0]);

    MetaData result2 = task2.Run(player1);
    EXPECT_EQ(result2, MetaData::DESTROY_MINION_SUCCESS);
    EXPECT_EQ(player2.GetField().size(), static_cast<size_t>(0));

    // Destroy Target Weapon
    Card weaponCard;
    player2.GetHero()->weapon = new Weapon(weaponCard);

    DestroyTask task3(EntityType::ENEMY_WEAPON, nullptr, nullptr);

    MetaData result3 = task3.Run(player1);
    EXPECT_EQ(result3, MetaData::DESTROY_WEAPON_SUCCESS);
    EXPECT_EQ(player2.GetHero()->HasWeapon(), false);
}
