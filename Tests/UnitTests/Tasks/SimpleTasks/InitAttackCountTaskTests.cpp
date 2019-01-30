// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Managers/GameAgent.hpp>
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
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    agent.GetPlayer1().SetID(100);

    MetaData result = init.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    TaskMeta meta;
    result = init.Run(agent.GetPlayer1(), meta);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);
    EXPECT_EQ(meta.GetID(), +TaskID::INIT_ATTACK_COUNT);
    EXPECT_EQ(meta.GetStatus(), MetaData::INIT_ATTACK_COUNT_SUCCESS);
    EXPECT_EQ(meta.GetUserID(), agent.GetPlayer1().GetID());
}

TEST(InitAttackCountTask, RunFrozen)
{
    InitAttackCountTask init;
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    Card card;

    Minion minion1(&agent, card);
    Minion minion2(&agent, card);
    Minion minion3(&agent, card);
    Minion minion4(&agent, card);
    Minion minion5(&agent, card);
    Minion minion6(&agent, card);

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

    agent.GetPlayer1().GetField().AddMinion(minion1, 0);
    agent.GetPlayer1().GetField().AddMinion(minion2, 1);
    agent.GetPlayer1().GetField().AddMinion(minion3, 2);
    agent.GetPlayer1().GetField().AddMinion(minion4, 3);
    agent.GetPlayer2().GetField().AddMinion(minion5, 0);
    agent.GetPlayer2().GetField().AddMinion(minion6, 1);

    MetaData result = init.Run(agent.GetPlayer2());
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion2.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion3.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion3.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion4.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion4.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion5.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5.attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion6.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion6.attackableCount, static_cast<size_t>(0));

    result = init.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1.attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion2.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2.attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion3.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion3.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion4.GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion4.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion5.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion6.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion6.attackableCount, static_cast<size_t>(0));

    result = init.Run(agent.GetPlayer2());
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion2.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion3.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion3.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion4.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion4.attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion5.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5.attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion6.GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion6.attackableCount, static_cast<size_t>(1));
}

TEST(InitAttackCountTask, RunWindFury)
{
    InitAttackCountTask init;
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    Card card;

    Minion minion1(&agent, card);
    Minion minion2(&agent, card);

    minion2.SetGameTag(GameTag::WINDFURY, 1);

    agent.GetPlayer1().GetField().AddMinion(minion1, 0);
    agent.GetPlayer1().GetField().AddMinion(minion2, 1);

    MetaData result = init.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1.attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion2.attackableCount, static_cast<size_t>(2));
}