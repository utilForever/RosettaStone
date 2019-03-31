// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Models/Weapon.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/EndTurnTask.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace TestUtils;

TEST(AttackTask, GetTaskID)
{
    const AttackTask attack(nullptr, nullptr);

    EXPECT_EQ(attack.GetTaskID(), +TaskID::ATTACK);
}

TEST(AttackTask, Default)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    auto card2 = GenerateMinionCard("minion2", 5, 4);

    PlayMinionCard(player1, card1);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card2);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), player2.GetHero()));
    EXPECT_EQ(p1Field.GetMinion(0)->health, p1Field.GetMinion(0)->maxHealth);
    EXPECT_EQ(static_cast<std::size_t>(player2.GetHero()->health),
              player2.GetHero()->maxHealth - p1Field.GetMinion(0)->GetAttack());

    EndTurnTask().Run(player1);

    Task::Run(player2, AttackTask(p2Field.GetMinion(0), p1Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 1);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 1);

    EndTurnTask().Run(player2);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetNumOfMinions(), 0u);
    EXPECT_EQ(p2Field.GetNumOfMinions(), 0u);

    auto card3 = GenerateMinionCard("minion3", 5, 6);
    auto card4 = GenerateMinionCard("minion4", 5, 4);

    PlayMinionCard(player1, card3);
    PlayMinionCard(player2, card4);

    EndTurnTask().Run(player1);
    EndTurnTask().Run(player2);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 1);
    EXPECT_EQ(p2Field.GetNumOfMinions(), 0u);

    auto card5 = GenerateMinionCard("minion5", 5, 4);

    p1Field.GetMinion(0)->SetAttack(1);
    PlayMinionCard(player2, card5);

    EndTurnTask().Run(player1);
    EndTurnTask().Run(player2);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetNumOfMinions(), 0u);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 3);
}

TEST(AttackTask, Weapon)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion1", 1, 10);

    player1.GetHero()->weapon = new Weapon();
    player1.GetHero()->weapon->SetAttack(4);
    player1.GetHero()->weapon->durability = 2;
    player1.GetHero()->weapon->SetOwner(player1);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p2Field = player2.GetField();

    Task::Run(player1, AttackTask(player1.GetHero(), p2Field.GetMinion(0)));

    EXPECT_EQ(player1.GetHero()->weapon->durability, 1u);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 6);

    EndTurnTask().Run(player1);
    EndTurnTask().Run(player2);

    Task::Run(player1, AttackTask(player1.GetHero(), p2Field.GetMinion(0)));

    EXPECT_EQ(player1.GetHero()->HasWeapon(), false);
    EXPECT_EQ(player1.GetHero()->GetAttack(), 0);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 2);
}

TEST(AttackTask, Charge)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card1 = GenerateMinionCard("minion1", 1, 10);
    auto card2 = GenerateMinionCard("minion1", 1, 10);
    card2.gameTags[GameTag::CHARGE] = 1;

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    PlayMinionCard(player1, card1);
    PlayMinionCard(player1, card2);
    PlayMinionCard(player2, card1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->numAttacked, 0u);

    Task::Run(player1, AttackTask(p1Field.GetMinion(1), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(1)->numAttacked, 1u);
}

TEST(AttackTask, Taunt)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion1", 1, 10);

    PlayMinionCard(player1, card);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    p2Field.GetMinion(1)->SetGameTag(GameTag::TAUNT, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p2Field.GetMinion(0)->health, 10);

    p2Field.GetMinion(1)->SetGameTag(GameTag::TAUNT, 0);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p2Field.GetMinion(0)->health, 9);
}

TEST(AttackTask, Stealth)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    p2Field.GetMinion(0)->SetGameTag(GameTag::STEALTH, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p2Field.GetMinion(0)->health, 10);

    p1Field.GetMinion(0)->SetGameTag(GameTag::STEALTH, 1);
    p2Field.GetMinion(0)->SetGameTag(GameTag::STEALTH, 0);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->GetGameTag(GameTag::STEALTH), 0);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 9);
}

TEST(AttackTask, Immune)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    p1Field.GetMinion(0)->SetGameTag(GameTag::IMMUNE, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 10);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 9);

    EndTurnTask().Run(player1);
    EndTurnTask().Run(player2);

    p1Field.GetMinion(0)->SetGameTag(GameTag::IMMUNE, 0);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 9);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 8);
}

TEST(AttackTask, Windfury)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->numAttacked, 1u);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->numAttacked, 1u);

    EndTurnTask().Run(player1);
    EndTurnTask().Run(player2);

    p1Field.GetMinion(0)->SetGameTag(GameTag::WINDFURY, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->numAttacked, 1u);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->numAttacked, 2u);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->numAttacked, 2u);
}

TEST(AttackTask, DivineShield)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    p1Field.GetMinion(0)->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 10);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 9);

    EndTurnTask().Run(player1);
    EndTurnTask().Run(player2);

    p2Field.GetMinion(0)->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 9);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 9);
}

TEST(AttackTask, Poisonous)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    p1Field.GetMinion(0)->SetGameTag(GameTag::POISONOUS, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 9);
    EXPECT_EQ(p2Field.GetNumOfMinions(), 0u);

    EndTurnTask().Run(player1);
    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    p1Field.GetMinion(0)->SetGameTag(GameTag::POISONOUS, 0);
    p2Field.GetMinion(0)->SetGameTag(GameTag::POISONOUS, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetNumOfMinions(), 0u);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 9);
}

TEST(AttackTask, Freeze)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;

    Game game(config);
    game.StartGame();

    Player& player1 = game.GetPlayer1();
    Player& player2 = game.GetPlayer2();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(player1, card);
    EndTurnTask().Run(player1);

    PlayMinionCard(player2, card);
    EndTurnTask().Run(player2);

    auto& p1Field = player1.GetField();
    auto& p2Field = player2.GetField();

    p1Field.GetMinion(0)->SetGameTag(GameTag::FREEZE, 1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p2Field.GetMinion(0)->GetGameTag(GameTag::FROZEN), 1);

    EndTurnTask().Run(player1);

    Task::Run(player1, AttackTask(p1Field.GetMinion(0), p2Field.GetMinion(0)));
    EXPECT_EQ(p1Field.GetMinion(0)->health, 9);
    EXPECT_EQ(p2Field.GetMinion(0)->health, 9);
}