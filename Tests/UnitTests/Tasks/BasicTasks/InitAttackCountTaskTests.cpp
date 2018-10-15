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
    BasicTasks::InitAttackCountTask init;
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

    Card card1;
    Card card2;
    Card card3;

    Minion* minion1 = new Minion(card1);
    Minion* minion2 = new Minion(card2);
    Minion* minion3 = new Minion(card3);

    minion2->gameTags[GameTag::FROZEN] = 1;
    minion3->gameTags[GameTag::FROZEN] = 2;

    gen.player1.field.emplace_back(minion1);
    gen.player1.field.emplace_back(minion2);
    gen.player1.field.emplace_back(minion3);

    MetaData result = init.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion2->gameTags[GameTag::FROZEN], static_cast<int>(0));
    EXPECT_EQ(minion2->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion3->gameTags[GameTag::FROZEN], static_cast<int>(1));
    EXPECT_EQ(minion3->attackableCount, static_cast<size_t>(0));
}

TEST(InitAttackCountTask, RunWindFury)
{
    BasicTasks::InitAttackCountTask init;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    Card card1;
    Card card2;

    Minion* minion1 = new Minion(card1);
    Minion* minion2 = new Minion(card2);

    minion2->gameTags[GameTag::WINDFURY] = 1;

    gen.player1.field.emplace_back(minion1);
    gen.player1.field.emplace_back(minion2);

    MetaData result = init.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::INIT_ATTACK_COUNT_SUCCESS);

    EXPECT_EQ(minion1->attackableCount, static_cast<size_t>(1));
    EXPECT_EQ(minion2->attackableCount, static_cast<size_t>(2));
}