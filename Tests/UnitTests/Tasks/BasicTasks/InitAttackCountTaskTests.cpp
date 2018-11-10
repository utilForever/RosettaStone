// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Tasks/BasicTasks/InitAttackCountTask.h>

using namespace Hearthstonepp;

TEST(InitAttackCountTask, GetTaskID)
{
    const BasicTasks::InitAttackCountTask init;
    EXPECT_EQ(init.GetTaskID(), +TaskID::INIT_ATTACK_COUNT);
}

TEST(InitAttackCountTask, Run)
{
    BasicTasks::InitAttackCountTask init;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    gen.player1.id = 100;

    MetaData result = init.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    TaskMeta meta;
    result = init.Run(gen.player1, gen.player2, meta);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);
    EXPECT_EQ(meta.id, +TaskID::INIT_ATTACK_COUNT);
    EXPECT_EQ(meta.status, MetaData::INIT_ATTACK_COUNT_SUCCESS);
    EXPECT_EQ(meta.userID, gen.player1.id);
}

TEST(InitAttackCountTask, RunFrozen)
{
    BasicTasks::InitAttackCountTask init;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    Card card;

    auto minion1 = new Minion(card);
    auto minion2 = new Minion(card);
    auto minion3 = new Minion(card);
    auto minion4 = new Minion(card);
    auto minion5 = new Minion(card);
    auto minion6 = new Minion(card);

    // Case 1
    minion6->SetGameTag(GameTag::FROZEN, 1);
    minion6->numTurnToUnfreeze = 2;
    // Case 2-1
    minion2->SetGameTag(GameTag::FROZEN, 1);
    minion2->attackableCount = 1;
    minion2->numTurnToUnfreeze = 1;
    // Case 2-2
    minion3->SetGameTag(GameTag::FROZEN, 1);
    minion3->attackableCount = 0;
    minion3->numTurnToUnfreeze = 3;
    minion4->SetGameTag(GameTag::FROZEN, 1);
    minion4->SetGameTag(GameTag::WINDFURY, 1);
    minion4->attackableCount = 1;
    minion4->numTurnToUnfreeze = 3;

    gen.player1.field.emplace_back(minion1);
    gen.player1.field.emplace_back(minion2);
    gen.player1.field.emplace_back(minion3);
    gen.player1.field.emplace_back(minion4);
    gen.player2.field.emplace_back(minion5);
    gen.player2.field.emplace_back(minion6);

    MetaData result = init.Run(gen.player2, gen.player1);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion2->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion3->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion3->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion4->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion4->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion5->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion6->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion6->attackableCount, static_cast<size_t>(0));

    result = init.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion2->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion3->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion3->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion4->GetGameTag(GameTag::FROZEN), 1);
    EXPECT_EQ(minion4->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion5->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion6->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion6->attackableCount, static_cast<size_t>(0));

    result = init.Run(gen.player2, gen.player1);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion1->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion2->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion2->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion3->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion3->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion4->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion4->attackableCount, static_cast<size_t>(0));
    EXPECT_EQ(minion5->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion5->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion6->GetGameTag(GameTag::FROZEN), 0);
    EXPECT_EQ(minion6->attackableCount, static_cast<size_t>(1));
}

TEST(InitAttackCountTask, RunWindFury)
{
    BasicTasks::InitAttackCountTask init;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    Card card1;
    Card card2;

    auto minion1 = new Minion(card1);
    auto minion2 = new Minion(card2);

    minion2->SetGameTag(GameTag::WINDFURY, 1);

    gen.player1.field.emplace_back(minion1);
    gen.player1.field.emplace_back(minion2);

    MetaData result = init.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion2->attackableCount, static_cast<size_t>(2));
}