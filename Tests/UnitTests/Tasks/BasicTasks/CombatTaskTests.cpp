// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/ResponseUtils.h>
#include <Utils/TestUtils.h>
#include "gtest/gtest.h"

#include <hspp/Tasks/BasicTasks/CombatTask.h>
#include <hspp/Tasks/BasicTasks/InitAttackCountTask.h>

using namespace Hearthstonepp;
using namespace BasicTasks;
using namespace TestUtils;

class CombatTester
{
 public:
    CombatTester()
        : m_gameAgent(CardClass::DRUID, CardClass::ROGUE, PLAYER1),
          m_taskAgent(m_gameAgent.GetTaskAgent())
    {
        // Do nothing
    }

    std::tuple<Player&, Player&> GetPlayer()
    {
        return { m_gameAgent.GetPlayer1(), m_gameAgent.GetPlayer2() };
    }

    void InitAttackCount(size_t player)
    {
        if (player == PLAYER1)
        {
            m_init.Run(m_gameAgent.GetPlayer1());
        }
        else
        {
            m_init.Run(m_gameAgent.GetPlayer2());
        }
    }

    void Attack(Entity* source, Entity* target, MetaData expected,
                size_t player)
    {
        MetaData result;

        if (player == PLAYER1)
        {
            result = CombatTask(m_taskAgent, source, target)
                         .Run(m_gameAgent.GetPlayer1());
        }
        else
        {
            result = CombatTask(m_taskAgent, source, target)
                         .Run(m_gameAgent.GetPlayer2());
        }

        EXPECT_EQ(result, expected);
    }

 private:
    GameAgent m_gameAgent;
    TaskAgent& m_taskAgent;

    InitAttackCountTask m_init;
};

TEST(CombatTask, GetTaskID)
{
    TaskAgent agent;
    const CombatTask combat(agent, nullptr, nullptr);
    EXPECT_EQ(combat.GetTaskID(), +TaskID::COMBAT);
}

TEST(CombatTask, Default)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    auto card2 = GenerateMinionCard("minion2", 5, 4);

    player1.field.emplace_back(new Minion(card1));
    player2.field.emplace_back(new Minion(card2));

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.hero, MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field[0]->health, player1.field[0]->maxHealth);
    EXPECT_EQ(player2.hero->health,
              player2.hero->maxHealth - player1.field[0]->GetAttack());

    tester.InitAttackCount(PLAYER2);

    tester.Attack(player2.field[0], player1.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER2);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(1));

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    auto card3 = GenerateMinionCard("minion3", 5, 6);
    auto card4 = GenerateMinionCard("minion4", 5, 4);

    player1.field.emplace_back(new Minion(card3));
    player2.field.emplace_back(new Minion(card4));

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    auto card5 = GenerateMinionCard("minion5", 5, 4);

    player1.field[0]->SetAttack(1);
    player2.field.emplace_back(new Minion(card5));

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(3));
}

// TEST(CombatTask, IndexOutOfRange)
//{
//    CombatTester tester;
//    auto [player1, player2] = tester.GetPlayer();
//    auto card = GenerateMinionCard("minion1", 1, 10);
//
//    player1.field.emplace_back(new Minion(card));
//    player2.field.emplace_back(new Minion(card));
//
//    tester.InitAttackCount(PLAYER1);
//
//    tester.Attack(player1.field[0], player2.field[1],
//    MetaData::COMBAT_DST_IDX_OUT_OF_RANGE, PLAYER1);
//    tester.Attack(player1.field[1], player2.field[0],
//    MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE, PLAYER1);
//}

TEST(CombatTask, Weapon)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.hero->weapon = new Weapon();
    player1.hero->weapon->SetAttack(4);
    player1.hero->weapon->SetDurability(2);
    player2.field.emplace_back(new Minion(card));

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.hero, player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);

    EXPECT_EQ(player1.hero->weapon->GetDurability(), 1);
    EXPECT_EQ(player2.field[0]->health, 6);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.hero, player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);

    EXPECT_EQ(player1.hero->weapon, nullptr);
    EXPECT_EQ(player1.hero->GetAttack(), 0);
    EXPECT_EQ(player2.field[0]->health, 2);
}

TEST(CombatTask, Charge)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player1.field[0]->SetGameTag(GameTag::CHARGE, 1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);

    player1.field[0]->SetGameTag(GameTag::CHARGE, 0);

    tester.Attack(player1.field[0], player2.field[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PLAYER1);
}

TEST(CombatTask, Taunt)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    tester.InitAttackCount(PLAYER1);

    player2.field[1]->SetGameTag(GameTag::TAUNT, 1);

    tester.Attack(player1.field[0], player2.field[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PLAYER1);

    player2.field[1]->SetGameTag(GameTag::TAUNT, 0);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
}

TEST(CombatTask, Stealth)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player2.field[0]->SetGameTag(GameTag::STEALTH, 1);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PLAYER1);

    player1.field[0]->SetGameTag(GameTag::STEALTH, 1);
    player2.field[0]->SetGameTag(GameTag::STEALTH, 0);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field[0]->GetGameTag(GameTag::STEALTH), 0);
}

TEST(CombatTask, Immune)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player1.field[0]->SetGameTag(GameTag::IMMUNE, 1);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field[0]->health, 10);
    EXPECT_EQ(player2.field[0]->health, 9);
}

TEST(CombatTask, Windfury)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    tester.Attack(player1.field[0], player2.field[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PLAYER1);

    player1.field[0]->SetGameTag(GameTag::WINDFURY, 1);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    tester.Attack(player1.field[0], player2.field[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PLAYER1);
}

TEST(CombatTask, DivineShield)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    tester.InitAttackCount(PLAYER1);

    player1.field[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field[0]->health, player1.field[0]->maxHealth);
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(9));

    player2.field[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(9));
}

TEST(CombatTask, Poisonous)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player1.field[0]->SetGameTag(GameTag::POISONOUS, 1);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.field.size(), static_cast<size_t>(0));

    player2.field.emplace_back(new Minion(card));

    player1.field[0]->SetGameTag(GameTag::POISONOUS, 0);
    player2.field[0]->SetGameTag(GameTag::POISONOUS, 1);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(9));
}

TEST(CombatTask, Freeze)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.field.emplace_back(new Minion(card));
    player2.field.emplace_back(new Minion(card));

    player1.field[0]->SetGameTag(GameTag::FREEZE, 1);

    tester.InitAttackCount(PLAYER1);

    tester.Attack(player1.field[0], player2.field[0], MetaData::COMBAT_SUCCESS,
                  PLAYER1);
    EXPECT_EQ(player2.field[0]->GetGameTag(GameTag::FROZEN), 1);

    tester.InitAttackCount(PLAYER2);

    tester.Attack(player2.field[0], player1.field[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PLAYER2);
    EXPECT_EQ(player1.field[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.field[0]->health, static_cast<size_t>(9));
}