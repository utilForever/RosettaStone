// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Commons/Constants.hpp>
#include <hspp/Models/Game.hpp>
#include <hspp/Models/Weapon.hpp>
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
        : m_game(CardClass::DRUID, CardClass::ROGUE, PlayerType::PLAYER1)
    {
        // Do nothing
    }

    std::tuple<Player&, Player&> GetPlayer()
    {
        return { m_game.GetPlayer1(), m_game.GetPlayer2() };
    }

    void InitAttackCount(PlayerType playerType)
    {
        if (playerType == PlayerType::PLAYER1)
        {
            InitAttackCountTask().Run(m_game.GetPlayer1());
        }
        else
        {
            InitAttackCountTask().Run(m_game.GetPlayer2());
        }
    }

    void Attack(Entity* source, Entity* target, TaskStatus expected,
                PlayerType playerType)
    {
        TaskStatus result;

        if (playerType == PlayerType::PLAYER1)
        {
            result = CombatTask(source, target).Run(m_game.GetPlayer1());
        }
        else
        {
            result = CombatTask(source, target).Run(m_game.GetPlayer2());
        }

        EXPECT_EQ(result, expected);
    }

 private:
    Game m_game;
};

TEST(CombatTask, GetTaskID)
{
    const CombatTask combat(nullptr, nullptr);

    EXPECT_EQ(combat.GetTaskID(), +TaskID::COMBAT);
}

TEST(CombatTask, Default)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    auto card2 = GenerateMinionCard("minion2", 5, 4);

    PlayMinionCard(player1, card1);
    PlayMinionCard(player2, card2);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    tester.Attack(player1Field.GetMinion(0), player2.GetHero(),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetMinion(0)->health,
              player1Field.GetMinion(0)->maxHealth);
    EXPECT_EQ(
        player2.GetHero()->health,
        player2.GetHero()->maxHealth - player1Field.GetMinion(0)->GetAttack());

    tester.InitAttackCount(PlayerType::PLAYER2);

    tester.Attack(player2Field.GetMinion(0), player1Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER2);
    EXPECT_EQ(player1Field.GetMinion(0)->health, 1);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetNumOfMinions(), 0u);
    EXPECT_EQ(player2Field.GetNumOfMinions(), 0u);

    auto card3 = GenerateMinionCard("minion3", 5, 6);
    auto card4 = GenerateMinionCard("minion4", 5, 4);

    PlayMinionCard(player1, card3);
    PlayMinionCard(player2, card4);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetMinion(0)->health, 1);
    EXPECT_EQ(player2Field.GetNumOfMinions(), 0u);

    auto card5 = GenerateMinionCard("minion5", 5, 4);

    player1Field.GetMinion(0)->SetAttack(1);
    PlayMinionCard(player2, card5);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetNumOfMinions(), 0u);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 3);
}

TEST(CombatTask, Weapon)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.GetHero()->weapon = new Weapon();
    player1.GetHero()->weapon->SetAttack(4);
    player1.GetHero()->weapon->SetDurability(2);
    player1.GetHero()->weapon->SetOwner(player1);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player2Field = player2.GetField();

    tester.Attack(player1.GetHero(), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);

    EXPECT_EQ(player1.GetHero()->weapon->GetDurability(), 1);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 6);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1.GetHero(), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);

    EXPECT_EQ(player1.GetHero()->HasWeapon(), false);
    EXPECT_EQ(player1.GetHero()->GetAttack(), 0);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 2);
}

TEST(CombatTask, Charge)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    player1Field.GetMinion(0)->SetGameTag(GameTag::CHARGE, 1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);

    player1Field.GetMinion(0)->SetGameTag(GameTag::CHARGE, 0);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);
}

TEST(CombatTask, Taunt)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion1", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    player2Field.GetMinion(1)->SetGameTag(GameTag::TAUNT, 1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);

    player2Field.GetMinion(1)->SetGameTag(GameTag::TAUNT, 0);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
}

TEST(CombatTask, Stealth)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    player2Field.GetMinion(0)->SetGameTag(GameTag::STEALTH, 1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);

    player1Field.GetMinion(0)->SetGameTag(GameTag::STEALTH, 1);
    player2Field.GetMinion(0)->SetGameTag(GameTag::STEALTH, 0);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetMinion(0)->GetGameTag(GameTag::STEALTH), 0);
}

TEST(CombatTask, Immune)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    player1Field.GetMinion(0)->SetGameTag(GameTag::IMMUNE, 1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetMinion(0)->health, 10);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 9);
}

TEST(CombatTask, Windfury)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);

    player1Field.GetMinion(0)->SetGameTag(GameTag::WINDFURY, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER1);
}

TEST(CombatTask, DivineShield)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    player1Field.GetMinion(0)->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetMinion(0)->health,
              player1Field.GetMinion(0)->maxHealth);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 9);

    player2Field.GetMinion(0)->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetMinion(0)->health, 9);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 9);
}

TEST(CombatTask, Poisonous)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    player1Field.GetMinion(0)->SetGameTag(GameTag::POISONOUS, 1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetMinion(0)->health, 9);
    EXPECT_EQ(player2Field.GetNumOfMinions(), 0u);

    PlayMinionCard(player2, card);

    player1Field.GetMinion(0)->SetGameTag(GameTag::POISONOUS, 0);
    player2Field.GetMinion(0)->SetGameTag(GameTag::POISONOUS, 1);

    tester.InitAttackCount(PlayerType::PLAYER1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player1Field.GetNumOfMinions(), 0u);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 9);
}

TEST(CombatTask, Freeze)
{
    CombatTester tester;
    auto [player1, player2] = tester.GetPlayer();
    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    PlayMinionCard(player2, card);

    tester.InitAttackCount(PlayerType::PLAYER1);

    auto& player1Field = player1.GetField();
    auto& player2Field = player2.GetField();

    player1Field.GetMinion(0)->SetGameTag(GameTag::FREEZE, 1);

    tester.Attack(player1Field.GetMinion(0), player2Field.GetMinion(0),
                  TaskStatus::COMBAT_SUCCESS, PlayerType::PLAYER1);
    EXPECT_EQ(player2Field.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);

    tester.InitAttackCount(PlayerType::PLAYER2);

    tester.Attack(player2Field.GetMinion(0), player1Field.GetMinion(0),
                  TaskStatus::COMBAT_SOURCE_CANT_ATTACK, PlayerType::PLAYER2);
    EXPECT_EQ(player1Field.GetMinion(0)->health, 9);
    EXPECT_EQ(player2Field.GetMinion(0)->health, 9);
}