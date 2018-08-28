#include "gtest/gtest.h"
#include <Utils/ResponseUtils.h>
#include <Utils/TestUtils.h>

#include <Tasks/BasicTasks/CombatTask.h>

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

    GameAgent agent(gen.player1, gen.player2);
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
