#include "gtest/gtest.h"
#include <Utils/ResponseUtils.h>
#include <Utils/TestUtils.h>

#include <Tasks/BasicTasks/CombatTask.h>
#include <Tasks/BasicTasks/InitAttackCountTask.h>

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

    BasicTasks::InitAttackCountTask init;
    BasicTasks::CombatTask combat(agent.GetTaskAgent());

    auto attack = [&](size_t src, size_t dst) {
        init.Run(gen.player1, gen.player2);
        init.Run(gen.player2, gen.player1);

        auto target = resp.Target(src, dst);
        MetaData result = combat.Run(gen.player1, gen.player2);
        EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);

        TaskMeta meta = target.get();
        EXPECT_EQ(meta.id, +TaskID::REQUIRE);
    };

    auto card1 = TestUtils::GenerateMinionCard("minion1", 3, 6);
    auto card2 = TestUtils::GenerateMinionCard("minion2", 5, 4);

    Minion minion1(card1.get());
    Minion minion2(card2.get());

    gen.player1.field.emplace_back(&minion1);
    gen.player2.field.emplace_back(&minion2);

    attack(1, 0);
    EXPECT_EQ(gen.player1.field[0]->health, gen.player1.field[0]->maxHealth);
    EXPECT_EQ(gen.player2.hero->health, gen.player2.hero->maxHealth - gen.player1.field[0]->attack);

    attack(1, 1);
    EXPECT_EQ(gen.player1.field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(gen.player2.field[0]->health, static_cast<size_t>(1));

    attack(1, 1);
    EXPECT_EQ(gen.player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(gen.player2.field.size(), static_cast<size_t>(0));

    auto card3 = TestUtils::GenerateMinionCard("minion3", 5, 6);
    auto card4 = TestUtils::GenerateMinionCard("minion4", 5, 4);

    Minion minion3(card3.get());
    Minion minion4(card4.get());

    gen.player1.field.emplace_back(&minion3);
    gen.player2.field.emplace_back(&minion4);

    attack(1, 1);
    EXPECT_EQ(gen.player1.field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(gen.player2.field.size(), static_cast<size_t>(0));

    auto card5 = TestUtils::GenerateMinionCard("minion5", 5, 4);

    Minion minion5(card5.get());

    gen.player1.field[0]->attack = 1;
    gen.player2.field.emplace_back(&minion5);

    attack(1, 1);
    EXPECT_EQ(gen.player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(gen.player2.field[0]->health, static_cast<size_t>(3));
}

TEST(CombatTask, CombatAlreadyAttacked)
{
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
