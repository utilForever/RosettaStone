// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Weapon.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Tasks/PlayerTasks/CombatTask.hpp>
#include <hspp/Tasks/SimpleTasks/InitAttackCountTask.hpp>

using namespace Hearthstonepp;
using namespace PlayerTasks;
using namespace SimpleTasks;
using namespace TestUtils;

class CombatTester
{
 public:
    CombatTester()
        : m_gameAgent(CardClass::DRUID, CardClass::ROGUE, PlayerType::PLAYER1),
          m_taskAgent(m_gameAgent.GetTaskAgent())
    {
        // Do nothing
    }

    std::tuple<Player&, Player&> GetPlayer()
    {
        return { m_gameAgent.GetPlayer1(), m_gameAgent.GetPlayer2() };
    }

    void InitAttackCount(PlayerType playerType)
    {
        if (playerType == PlayerType::PLAYER1)
        {
            InitAttackCountTask().Run(m_gameAgent.GetPlayer1());
        }
        else
        {
            InitAttackCountTask().Run(m_gameAgent.GetPlayer2());
        }
    }

    void Attack(Entity* source, Entity* target, MetaData expected,
                PlayerType playerType)
    {
        MetaData result;

        if (playerType == PlayerType::PLAYER1)
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

    player1.GetField().emplace_back(new Minion(card1));
    player2.GetField().emplace_back(new Minion(card2));

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetHero(),
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField()[0]->health, player1.GetField()[0]->maxHealth);
    EXPECT_EQ(
        player2.GetHero()->health,
        player2.GetHero()->maxHealth - player1.GetField()[0]->GetAttack());

    tester.InitAttackCount(PlayerType::PLAYER2);

    tester.Attack(player2.GetField()[0], player1.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER2);
    EXPECT_EQ(player1.GetField()[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(player2.GetField()[0]->health, static_cast<size_t>(1));

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField().size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.GetField().size(), static_cast<size_t>(0));

    auto card3 = GenerateMinionCard("minion3", 5, 6);
    auto card4 = GenerateMinionCard("minion4", 5, 4);

    player1.GetField().emplace_back(new Minion(card3));
    player2.GetField().emplace_back(new Minion(card4));

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField()[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(player2.GetField().size(), static_cast<size_t>(0));

    auto card5 = GenerateMinionCard("minion5", 5, 4);

    player1.GetField()[0]->SetAttack(1);
    player2.GetField().emplace_back(new Minion(card5));

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField().size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.GetField()[0]->health, static_cast<size_t>(3));
}

TEST(CombatTask, Weapon)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.GetHero()->weapon = new Weapon();
    player1.GetHero()->weapon->SetAttack(4);
    player1.GetHero()->weapon->SetDurability(2);
    player2.GetField().emplace_back(new Minion(card));

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetHero(), player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);

    EXPECT_EQ(player1.GetHero()->weapon->GetDurability(), 1);
    EXPECT_EQ(player2.GetField()[0]->health, 6);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetHero(), player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);

    EXPECT_EQ(player1.GetHero()->HasWeapon(), false);
    EXPECT_EQ(player1.GetHero()->GetAttack(), 0);
    EXPECT_EQ(player2.GetField()[0]->health, 2);
}

TEST(CombatTask, Charge)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    player1.GetField()[0]->SetGameTag(GameTag::CHARGE, 1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);

    player1.GetField()[0]->SetGameTag(GameTag::CHARGE, 0);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);
}

TEST(CombatTask, Taunt)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    tester.InitAttackCount(PlayerType::PLAYER1);

    player2.GetField()[1]->SetGameTag(GameTag::TAUNT, 1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);

    player2.GetField()[1]->SetGameTag(GameTag::TAUNT, 0);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
}

TEST(CombatTask, Stealth)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    player2.GetField()[0]->SetGameTag(GameTag::STEALTH, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);

    player1.GetField()[0]->SetGameTag(GameTag::STEALTH, 1);
    player2.GetField()[0]->SetGameTag(GameTag::STEALTH, 0);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField()[0]->GetGameTag(GameTag::STEALTH), 0);
}

TEST(CombatTask, Immune)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    player1.GetField()[0]->SetGameTag(GameTag::IMMUNE, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField()[0]->health, 10);
    EXPECT_EQ(player2.GetField()[0]->health, 9);
}

TEST(CombatTask, Windfury)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);

    player1.GetField()[0]->SetGameTag(GameTag::WINDFURY, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);
}

TEST(CombatTask, DivineShield)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    tester.InitAttackCount(PlayerType::PLAYER1);

    player1.GetField()[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField()[0]->health, player1.GetField()[0]->maxHealth);
    EXPECT_EQ(player2.GetField()[0]->health, static_cast<size_t>(9));

    player2.GetField()[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField()[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.GetField()[0]->health, static_cast<size_t>(9));
}

TEST(CombatTask, Poisonous)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    player1.GetField()[0]->SetGameTag(GameTag::POISONOUS, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField()[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.GetField().size(), static_cast<size_t>(0));

    player2.GetField().emplace_back(new Minion(card));

    player1.GetField()[0]->SetGameTag(GameTag::POISONOUS, 0);
    player2.GetField()[0]->SetGameTag(GameTag::POISONOUS, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1.GetField().size(), static_cast<size_t>(0));
    EXPECT_EQ(player2.GetField()[0]->health, static_cast<size_t>(9));
}

TEST(CombatTask, Freeze)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    player1.GetField().emplace_back(new Minion(card));
    player2.GetField().emplace_back(new Minion(card));

    player1.GetField()[0]->SetGameTag(GameTag::FREEZE, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetField()[0], player2.GetField()[0],
                  MetaData::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player2.GetField()[0]->GetGameTag(GameTag::FROZEN), 1);

    tester.InitAttackCount(PlayerType::PLAYER2);

    tester.Attack(player2.GetField()[0], player1.GetField()[0],
                  MetaData::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER2);
    EXPECT_EQ(player1.GetField()[0]->health, static_cast<size_t>(9));
    EXPECT_EQ(player2.GetField()[0]->health, static_cast<size_t>(9));
}