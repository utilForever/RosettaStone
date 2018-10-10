// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/ResponseUtils.h>
#include <Utils/TestUtils.h>

#include <hspp/Tasks/BasicTasks/CombatTask.h>

using namespace Hearthstonepp;

TEST(CombatTask, GetTaskID)
{
    TaskAgent agent;
    BasicTasks::CombatTask combat(agent);
    EXPECT_EQ(combat.GetTaskID(), +TaskID::COMBAT);
}

TEST(CombatTask, CombatDefault)
{
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    GameAgent agent(std::move(gen.player1), std::move(gen.player2));
    TestUtils::AutoResponder resp(agent);
    BasicTasks::CombatTask combat(agent.GetTaskAgent());

    
}

TEST(CombatTask, CombatTaunt)
{

}

TEST(CombatTask, CombatStealth)
{

}

TEST(CombatTask, CombatImmune)
{

}

TEST(CombatTask, CombatAttackCount)
{

}

TEST(CombatTask, CombatDivineShield)
{

}

TEST(CombatTask, Poisonous)
{

}
