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
          m_agent(std::move(m_gen.player1), std::move(m_gen.player2)),
          m_resp(m_agent),
          m_combat(m_agent.GetTaskAgent())
    {
        // Do Nothing
    }

    std::tuple<Player&, Player&> GetPlayer()
    {
        return { m_agent.GetPlayer1(), m_agent.GetPlayer2() };
    }

    void Attack(size_t src, size_t dst, MetaData expected, bool init = false)
    {
        if (init)
        {
            m_init.Run(m_agent.GetPlayer1(), m_agent.GetPlayer2());
            m_init.Run(m_agent.GetPlayer2(), m_agent.GetPlayer1());
        }
        auto target = m_resp.Target(src, dst);
        MetaData result =
            m_combat.Run(m_agent.GetPlayer1(), m_agent.GetPlayer2());
        EXPECT_EQ(result, expected);

        TaskMeta meta = target.get();
        EXPECT_EQ(meta.id, +TaskID::REQUIRE);
    }

 private:
    TestUtils::PlayerGenerator m_gen;

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

TEST(CombatTask, Default)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();

    auto card1 = TestUtils::GenerateMinionCard("minion1", 3, 6);
    auto card2 = TestUtils::GenerateMinionCard("minion2", 5, 4);

    player1.field.emplace_back(new Minion(card1));
    player2.field.emplace_back(new Minion(card2));

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

    player1.field.emplace_back(new Minion(card3));
    player2.field.emplace_back(new Minion(card4));

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    auto card5 = TestUtils::GenerateMinionCard("minion5", 5, 4);

    player1.field[0]->attack = 1;
    player2.field.emplace_back(new Minion(card5));

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(3));
}

TEST(CombatTask, IndexOutOfRange)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion1", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    tester.Attack(1, 2, MetaData::COMBAT_DST_IDX_OUT_OF_RANGE, true);
    tester.Attack(2, 1, MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE, true);
}

TEST(CombatTask, Taunt)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion1", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player2.field[1]->gameTags[+GameTag::TAUNT] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_FIELD_HAVE_TAUNT, true);

    player2.field[1]->gameTags[+GameTag::TAUNT] = 0;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
}

TEST(CombatTask, Stealth)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player2.field[0]->gameTags[+GameTag::STEALTH] = 1;

    tester.Attack(1, 1, MetaData::COMBAT_TARGET_STEALTH, true);

    player1.field[0]->gameTags[+GameTag::STEALTH] = 1;
    player2.field[0]->gameTags[+GameTag::STEALTH] = 0;

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field[0]->gameTags[+GameTag::STEALTH], 0);
}

TEST(CombatTask, Immune)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player2.field[0]->gameTags[+GameTag::IMMUNE] = 1;

    tester.Attack(1, 1, MetaData::COMBAT_TARGET_IMMUNE, true);
}

TEST(CombatTask, Windfury)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    tester.Attack(1, 1, MetaData::COMBAT_ALREADY_ATTACKED);

    player1.field[0]->gameTags[+GameTag::WINDFURY] = 1;

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS);
    tester.Attack(1, 1, MetaData::COMBAT_ALREADY_ATTACKED);
}

TEST(CombatTask, DivineShield)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player1.field[0]->gameTags[+GameTag::DIVINE_SHIELD] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);

    EXPECT_EQ(player1.field[0]->health, player1.field[0]->maxHealth);
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(9));

    player2.field[0]->gameTags[+GameTag::DIVINE_SHIELD] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);

    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(9));
}

TEST(CombatTask, Poisonous)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = TestUtils::GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player1.field[0]->gameTags[+GameTag::POISONOUS] = 1;
    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);

    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    player2.field.emplace_back(new Minion(card));

    player1.field[0]->gameTags[+GameTag::POISONOUS] = 0;
    player2.field[0]->gameTags[+GameTag::POISONOUS] = 1;

    tester.Attack(1, 1, MetaData::COMBAT_SUCCESS, true);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(9));
}
