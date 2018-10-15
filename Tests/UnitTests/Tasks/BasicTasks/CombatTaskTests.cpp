// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/ResponseUtils.h>
#include <Utils/TestUtils.h>

#include <hspp/Tasks/BasicTasks/CombatTask.h>
#include <hspp/Tasks/BasicTasks/InitAttackCountTask.h>

using namespace Hearthstonepp;

class CombatTester
{
 public:
    CombatTester()
        : m_gen(CardClass::DRUID, CardClass::ROGUE),
          m_player1(m_gen.player1),
          m_player2(m_gen.player2),
          m_agent(m_player1, m_player2),
          m_resp(m_agent),
          m_combat(m_agent.GetTaskAgent())
    {
        // Do Nothing
    }

    std::tuple<Player&, Player&> GetPlayer()
    {
        return {m_player1, m_player2};
    }

    void Attack(size_t src, size_t dst, MetaData expected, bool init = false)
    {
        if (init)
        {
            m_init.Run(m_player1, m_player2);
            m_init.Run(m_player2, m_player1);
        }
        auto target = m_resp.Target(src, dst);
        MetaData result = m_combat.Run(m_player1, m_player2);
        EXPECT_EQ(result, expected);

        TaskMeta meta = target.get();
        EXPECT_EQ(meta.id, +TaskID::REQUIRE);
    }

 private:
    TestUtils::PlayerGenerator m_gen;
    Player& m_player1;
    Player& m_player2;

    GameAgent m_agent;
    TestUtils::AutoResponder m_resp;

    BasicTasks::CombatTask m_combat;
    BasicTasks::InitAttackCountTask m_init;
};

TEST(CombatTask, GetTaskID)
{
    TaskAgent agent;
    BasicTasks::CombatTask combat(agent);
    EXPECT_EQ(combat.GetTaskID(), +TaskID::COMBAT);
}

TEST(CombatTask, CombatDefault)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();

    auto card1 = TestUtils::GenerateMinionCard("minion1", 3, 6);
    auto card2 = TestUtils::GenerateMinionCard("minion2", 5, 4);

    Minion minion1(*card1.get());
    Minion minion2(*card2.get());

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);

    tester.Attack(1, 0, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field[0]->health, player1.field[0]->maxHealth);
    EXPECT_EQ(player2.hero->health,
              player2.hero->maxHealth - player1.field[0]->attack);

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(1));

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    auto card3 = TestUtils::GenerateMinionCard("minion3", 5, 6);
    auto card4 = TestUtils::GenerateMinionCard("minion4", 5, 4);

    Minion minion3(*card3.get());
    Minion minion4(*card4.get());

    player1.field.emplace_back(&minion3);
    player2.field.emplace_back(&minion4);

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    auto card5 = TestUtils::GenerateMinionCard("minion5", 5, 4);

    Minion minion5(*card5.get());

    player1.field[0]->attack = 1;
    player2.field.emplace_back(&minion5);

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(3));
}

TEST(CombatTask, IndexOutOfRange)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion1", 1, 10);

    Minion minion1(*card.get());
    Minion minion2(*card.get());

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);

    tester.Attack(1, 2, MetaData::COMBAT_DST_IDX_OUT_OF_RANGE, true);
    tester.Attack(2, 1, MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE, true);
}

TEST(CombatTask, CombatTaunt)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion1", 1, 10);

    Minion minion1(*card.get());
    Minion minion2(*card.get());
    Minion minion3(*card.get());

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);
    player2.field.emplace_back(&minion3);

    minion3.gameTags[+GameTag::TAUNT] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_FIELD_HAVE_TAUNT, true);

    minion3.gameTags[+GameTag::TAUNT] = 0;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
}

TEST(CombatTask, CombatStealth)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    Minion minion1(*card.get());
    Minion minion2(*card.get());
    minion2.gameTags[+GameTag::STEALTH] = 1;

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);

    tester.Attack(1, 1, MetaData::COMBAT_TARGET_STEALTH, true);

    minion1.gameTags[+GameTag::STEALTH] = 1;
    minion2.gameTags[+GameTag::STEALTH] = 0;

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(minion1.gameTags[+GameTag::STEALTH], 0);
}

TEST(CombatTask, CombatImmune)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    Minion minion1(*card.get());
    Minion minion2(*card.get());
    minion2.gameTags[+GameTag::IMMUNE] = 1;

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);

    tester.Attack(1, 1, MetaData::COMBAT_TARGET_IMMUNE, true);
}

TEST(CombatTask, CombatAttackCount)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    Minion minion1(*card.get());
    Minion minion2(*card.get());

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    tester.Attack(1, 1, MetaData::COMBAT_ALREADY_ATTACKED);

    minion1.gameTags[+GameTag::WINDFURY] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS);
    tester.Attack(1, 1, MetaData::COMBAT_ALREADY_ATTACKED);
}

TEST(CombatTask, CombatDivineShield)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    Minion minion1(*card.get());
    Minion minion2(*card.get());

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);

    minion1.gameTags[+GameTag::DIVINE_SHIELD] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);

    EXPECT_EQ(minion1.health, minion1.maxHealth);
    EXPECT_EQ(minion2.health, static_cast<size_t>(9));

    minion2.gameTags[+GameTag::DIVINE_SHIELD] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);

    EXPECT_EQ(minion1.health, static_cast<size_t>(9));
    EXPECT_EQ(minion2.health, static_cast<size_t>(9));
}

TEST(CombatTask, Poisonous)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    Minion minion1(*card.get());
    Minion minion2(*card.get());

    player1.field.emplace_back(&minion1);
    player2.field.emplace_back(&minion2);

    minion1.gameTags[+GameTag::POISONOUS] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);

    EXPECT_EQ(minion1.health, static_cast<size_t>(9));
    EXPECT_EQ(minion2.health, static_cast<size_t>(0));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    Minion minion3(*card.get());
    player2.field.emplace_back(&minion3);

    minion1.gameTags[+GameTag::POISONOUS] = 0;
    minion3.gameTags[+GameTag::POISONOUS] = 1;

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(minion1.health, static_cast<size_t>(0));
    EXPECT_EQ(minion3.health, static_cast<size_t>(9));
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
}
