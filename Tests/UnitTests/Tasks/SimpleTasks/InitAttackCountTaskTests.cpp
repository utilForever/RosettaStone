// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Models/Game.hpp>
#include <hspp/Models/Minion.hpp>
#include <hspp/Tasks/SimpleTasks/InitAttackCountTask.hpp>

using namespace Hearthstonepp;
using namespace SimpleTasks;

TEST(InitAttackCountTask, GetTaskID)
{
    const InitAttackCountTask init;
    EXPECT_EQ(init.GetTaskID(), +TaskID::INIT_ATTACK_COUNT);
}

TEST(InitAttackCountTask, Run)
{
    InitAttackCountTask init;
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    game.GetPlayer1().SetID(100);

    TaskStatus result = init.Run(game.GetPlayer1());
    EXPECT_EQ(result, TaskStatus::INIT_ATTACK_COUNT_SUCCESS);
}

TEST(InitAttackCountTask, RunFrozen)
{
    InitAttackCountTask init;
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    Card card;

    Minion minion1(game.GetPlayer1(), card);
    Minion minion2(game.GetPlayer1(), card);
    Minion minion3(game.GetPlayer1(), card);
    Minion minion4(game.GetPlayer1(), card);
    Minion minion5(game.GetPlayer2(), card);
    Minion minion6(game.GetPlayer2(), card);

    // Case 1
    minion6.SetGameTag(GameTag::FROZEN, 1);
    minion6.numTurnToUnfreeze = 2;
    // Case 2-1
    minion2.SetGameTag(GameTag::FROZEN, 1);
    minion2.attackableCount = 1;
    minion2.numTurnToUnfreeze = 1;
    // Case 2-2
    minion3.SetGameTag(GameTag::FROZEN, 1);
    minion3.attackableCount = 0;
    minion3.numTurnToUnfreeze = 3;
    minion4.SetGameTag(GameTag::FROZEN, 1);
    minion4.SetGameTag(GameTag::WINDFURY, 1);
    minion4.attackableCount = 1;
    minion4.numTurnToUnfreeze = 3;

    game.GetPlayer1().GetField().AddMinion(minion1, 0);
    game.GetPlayer1().GetField().AddMinion(minion2, 1);
    game.GetPlayer1().GetField().AddMinion(minion3, 2);
    game.GetPlayer1().GetField().AddMinion(minion4, 3);
    game.GetPlayer2().GetField().AddMinion(minion5, 0);
    game.GetPlayer2().GetField().AddMinion(minion6, 1);

    TaskStatus result = init.Run(game.GetPlayer2());
    EXPECT_EQ(result, TaskStatus::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1.attackableCount, 0u);
    EXPECT_EQ(minion2.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2.attackableCount, 0u);
    EXPECT_EQ(minion3.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion3.attackableCount, 0u);
    EXPECT_EQ(minion4.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion4.attackableCount, 0u);
    EXPECT_EQ(minion5.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5.attackableCount, 1u);
    EXPECT_EQ(minion6.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion6.attackableCount, 0u);

    result = init.Run(game.GetPlayer1());
    EXPECT_EQ(result, TaskStatus::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1.attackableCount, 1u);
    EXPECT_EQ(minion2.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2.attackableCount, 1u);
    EXPECT_EQ(minion3.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion3.attackableCount, 0u);
    EXPECT_EQ(minion4.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion4.attackableCount, 0u);
    EXPECT_EQ(minion5.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5.attackableCount, 0u);
    EXPECT_EQ(minion6.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion6.attackableCount, 0u);

    result = init.Run(game.GetPlayer2());
    EXPECT_EQ(result, TaskStatus::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1.attackableCount, 0u);
    EXPECT_EQ(minion2.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2.attackableCount, 0u);
    EXPECT_EQ(minion3.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion3.attackableCount, 0u);
    EXPECT_EQ(minion4.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion4.attackableCount, 0u);
    EXPECT_EQ(minion5.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5.attackableCount, 1u);
    EXPECT_EQ(minion6.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion6.attackableCount, 1u);
}

TEST(InitAttackCountTask, RunWindFury)
{
    InitAttackCountTask init;
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    Card card;

    Minion minion1(game.GetPlayer1(), card);
    Minion minion2(game.GetPlayer1(), card);

    minion2.SetGameTag(GameTag::WINDFURY, 1);

    game.GetPlayer1().GetField().AddMinion(minion1, 0);
    game.GetPlayer1().GetField().AddMinion(minion2, 1);

    TaskStatus result = init.Run(game.GetPlayer1());
    EXPECT_EQ(result, TaskStatus::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.attackableCount, 1u);
    EXPECT_EQ(minion2.attackableCount, 2u);
}