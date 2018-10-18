// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Tasks/BasicTasks/DestroyTask.h>

using namespace Hearthstonepp;

TEST(DestroyTask, GetTaskID)
{
    BasicTasks::DestroyTask task(EntityType::EMPTY);
    EXPECT_EQ(task.GetTaskID(), +TaskID::DESTROY);
}

TEST(DestroyTask, Run)
{
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);
    Player& player1 = gen.player1;
    Player& player2 = gen.player2;

    auto card = TestUtils::GenerateMinionCard("minion1", 1, 1);

    // Destroy Source Minion
    player1.field.emplace_back(new Minion(card));

    BasicTasks::DestroyTask task(EntityType::SOURCE);
    task.source = player1.field[0];

    MetaData result = task.Run(player1, player2);
    EXPECT_EQ(result, MetaData::DESTROY_MINION_SUCCESS);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));

    // Destroy Target Minion
    player2.field.emplace_back(new Minion(card));

    BasicTasks::DestroyTask task2(EntityType::TARGET);
    task2.target = player2.field[0];

    MetaData result2 = task2.Run(player1, player2);
    EXPECT_EQ(result2, MetaData::DESTROY_MINION_SUCCESS);
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    // Destroy Target Weapon
    Card weaponCard;
    player2.hero->weapon = new Weapon(weaponCard);

    BasicTasks::DestroyTask task3 = BasicTasks::DestroyTask(EntityType::OPPONENT_WEAPON);

    MetaData result3 = task3.Run(player1, player2);
    EXPECT_EQ(result3, MetaData::DESTROY_WEAPON_SUCCESS);
    EXPECT_EQ(player2.hero->weapon, static_cast<const Weapon*>(nullptr));
}
