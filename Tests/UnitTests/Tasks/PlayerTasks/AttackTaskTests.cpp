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

    EXPECT_EQ(attack.GetTaskID(), TaskID::ATTACK);
}

TEST(AttackTask, Default)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();
    auto& opField = opPlayer.GetFieldZone();

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    auto card2 = GenerateMinionCard("minion2", 5, 4);

    PlayMinionCard(curPlayer, card1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    PlayMinionCard(opPlayer, card2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer.GetHero()));
    EXPECT_EQ(curField[0]->GetHealth(), 6);
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, AttackTask(opField[0], curField[0]));
    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField.GetCount(), 0);
    EXPECT_EQ(opField.GetCount(), 0);

    auto card3 = GenerateMinionCard("minion3", 5, 6);
    auto card4 = GenerateMinionCard("minion4", 5, 4);

    PlayMinionCard(curPlayer, card3);
    PlayMinionCard(opPlayer, card4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(opField.GetCount(), 0);

    auto card5 = GenerateMinionCard("minion5", 5, 4);

    curField[0]->SetAttack(1);
    PlayMinionCard(opPlayer, card5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField.GetCount(), 0);
    EXPECT_EQ(opField[0]->GetHealth(), 3);
}

TEST(AttackTask, Weapon)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& opField = opPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion1", 1, 10);

    curPlayer.GetHero()->weapon = new Weapon();
    curPlayer.GetHero()->weapon->SetAttack(4);
    curPlayer.GetHero()->weapon->SetDurability(2);
    curPlayer.GetHero()->weapon->owner = &curPlayer;

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    PlayMinionCard(opPlayer, card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curPlayer.GetHero(), opField[0]));

    EXPECT_EQ(curPlayer.GetHero()->weapon->GetDurability(), 1);
    EXPECT_EQ(opField[0]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curPlayer.GetHero(), opField[0]));

    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), false);
    EXPECT_EQ(curPlayer.GetHero()->GetAttack(), 0);
    EXPECT_EQ(opField[0]->GetHealth(), 2);
}

TEST(AttackTask, ZeroAttack)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion1", 0, 6);

    PlayMinionCard(curPlayer, card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);
}

TEST(AttackTask, Charge)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();
    auto& opField = opPlayer.GetFieldZone();

    auto card1 = GenerateMinionCard("minion1", 1, 10);
    auto card2 = GenerateMinionCard("minion1", 1, 10);
    card2.gameTags[GameTag::CHARGE] = 1;

    PlayMinionCard(curPlayer, card1);
    PlayMinionCard(curPlayer, card2);
    PlayMinionCard(opPlayer, card1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetNumAttacksThisTurn(), 0);

    game.Process(curPlayer, AttackTask(curField[1], opField[0]));
    EXPECT_EQ(curField[1]->GetNumAttacksThisTurn(), 1);
}

TEST(AttackTask, Taunt)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();
    auto& opField = opPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion1", 1, 10);

    PlayMinionCard(curPlayer, card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    PlayMinionCard(opPlayer, card);
    PlayMinionCard(opPlayer, card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    opField[1]->SetGameTag(GameTag::TAUNT, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(opField[0]->GetHealth(), 10);

    opField[1]->SetGameTag(GameTag::TAUNT, 0);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(opField[0]->GetHealth(), 9);
}

TEST(AttackTask, Stealth)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();
    auto& opField = opPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    PlayMinionCard(opPlayer, card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    opField[0]->SetGameTag(GameTag::STEALTH, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(opField[0]->GetHealth(), 10);

    curField[0]->SetGameTag(GameTag::STEALTH, 1);
    opField[0]->SetGameTag(GameTag::STEALTH, 0);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetGameTag(GameTag::STEALTH), 0);
    EXPECT_EQ(opField[0]->GetHealth(), 9);
}

TEST(AttackTask, Immune)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();
    auto& opField = opPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    PlayMinionCard(opPlayer, card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    curField[0]->SetGameTag(GameTag::IMMUNE, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetHealth(), 10);
    EXPECT_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    curField[0]->SetGameTag(GameTag::IMMUNE, 0);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetHealth(), 9);
    EXPECT_EQ(opField[0]->GetHealth(), 8);
}

TEST(AttackTask, Windfury)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();
    auto& opField = opPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    PlayMinionCard(opPlayer, card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    curField[0]->SetGameTag(GameTag::WINDFURY, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetNumAttacksThisTurn(), 2);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetNumAttacksThisTurn(), 2);
}

TEST(AttackTask, DivineShield)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();
    auto& opField = opPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    PlayMinionCard(opPlayer, card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    curField[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetHealth(), 10);
    EXPECT_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    opField[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    EXPECT_EQ(curField[0]->GetHealth(), 9);
    EXPECT_EQ(opField[0]->GetHealth(), 9);
}

TEST(AttackTask, Silence)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    auto& curField = curPlayer.GetFieldZone();

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, card);
    curField[0]->SetGameTag(GameTag::CANT_ATTACK, 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 30);

    curField[0]->Silence();

    game.Process(curPlayer, AttackTask(curField[0], opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 29);
}