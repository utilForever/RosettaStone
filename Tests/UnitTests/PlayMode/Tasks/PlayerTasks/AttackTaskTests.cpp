// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Models/Weapon.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace TestUtils;

TEST_CASE("[AttackTask] - Default")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    auto card2 = GenerateMinionCard("minion2", 5, 4);

    PlayMinionCard(curPlayer, &card1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(opField[0], curField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);

    auto card3 = GenerateMinionCard("minion3", 5, 6);
    auto card4 = GenerateMinionCard("minion4", 5, 4);

    PlayMinionCard(curPlayer, &card3);
    PlayMinionCard(opPlayer, &card4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opField.GetCount(), 0);

    auto card5 = GenerateMinionCard("minion5", 5, 4);

    curField[0]->SetAttack(1);
    PlayMinionCard(opPlayer, &card5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

TEST_CASE("[AttackTask] - Weapon")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion1", 1, 10);

    const auto weapon =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    game.Process(curPlayer, PlayCardTask::Weapon(weapon));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), opField[0]));

    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), opField[0]));

    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

TEST_CASE("[AttackTask] - ZeroAttack")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion1", 0, 6);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
}

TEST_CASE("[AttackTask] - Charge")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 1, 10);
    auto card2 = GenerateMinionCard("minion1", 1, 10);
    card2.gameTags[GameTag::CHARGE] = 1;

    PlayMinionCard(curPlayer, &card1);
    PlayMinionCard(curPlayer, &card2);
    PlayMinionCard(opPlayer, &card1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 0);

    game.Process(curPlayer, AttackTask(curField[1], opField[0]));
    CHECK_EQ(curField[1]->GetNumAttacksThisTurn(), 1);
}

TEST_CASE("[AttackTask] - Taunt")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion1", 1, 10);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);
    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opField[1]->SetGameTag(GameTag::TAUNT, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(opField[0]->GetHealth(), 10);

    opField[1]->SetGameTag(GameTag::TAUNT, 0);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(opField[0]->GetHealth(), 9);
}

TEST_CASE("[AttackTask] - Stealth")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opField[0]->SetGameTag(GameTag::STEALTH, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(opField[0]->GetHealth(), 10);

    curField[0]->SetGameTag(GameTag::STEALTH, 1);
    opField[0]->SetGameTag(GameTag::STEALTH, 0);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::STEALTH), 0);
    CHECK_EQ(opField[0]->GetHealth(), 9);
}

TEST_CASE("[AttackTask] - Immune")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::IMMUNE, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::IMMUNE, 0);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(opField[0]->GetHealth(), 8);
}

TEST_CASE("[AttackTask] - Windfury")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::WINDFURY, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 2);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 2);
}

TEST_CASE("[AttackTask] - Mega-Windfury")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::MEGA_WINDFURY, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 2);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 3);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 4);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 4);
}

TEST_CASE("[AttackTask] - DivineShield")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opField[0]->SetGameTag(GameTag::DIVINE_SHIELD, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(opField[0]->GetHealth(), 9);
}

TEST_CASE("[AttackTask] - Poisonous")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::POISONOUS, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::POISONOUS, 0);
    opField[0]->SetGameTag(GameTag::POISONOUS, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 9);
}

TEST_CASE("[AttackTask] - Freeze")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);
    PlayMinionCard(curPlayer, &card);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    PlayMinionCard(opPlayer, &card);
    PlayMinionCard(opPlayer, &card);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    curField[0]->SetGameTag(GameTag::FREEZE, 1);
    opField[1]->SetGameTag(GameTag::FREEZE, 1);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(opField[0]->IsFrozen(), true);

    game.Process(curPlayer, AttackTask(curField[1], opField[1]));
    CHECK_EQ(curField[1]->IsFrozen(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->IsFrozen(), true);
    CHECK_EQ(opField[0]->IsFrozen(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->IsFrozen(), true);
    CHECK_EQ(opField[0]->IsFrozen(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->IsFrozen(), false);
    CHECK_EQ(opField[0]->IsFrozen(), false);
}

TEST_CASE("[AttackTask] - Silence")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion", 1, 10);

    PlayMinionCard(curPlayer, &card);
    curField[0]->SetGameTag(GameTag::CANT_ATTACK, 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    curField[0]->Silence();

    game.Process(curPlayer, AttackTask(curField[0], opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
}

TEST_CASE("[AttackTask] - Rush")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card = GenerateMinionCard("minion1", 1, 10);
    card.gameTags[GameTag::RUSH] = 1;

    PlayMinionCard(curPlayer, &card);
    PlayMinionCard(opPlayer, &card);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 0);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[0], opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);
}

TEST_CASE("[AttackTask] - Reborn")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 10, 1);
    auto card2 = GenerateMinionCard("minion1", 1, 10);
    card1.gameTags[GameTag::RUSH] = 1;
    card2.gameTags[GameTag::REBORN] = 1;

    PlayMinionCard(curPlayer, &card1);
    PlayMinionCard(opPlayer, &card2);

    CHECK_EQ(opField[0]->HasReborn(), true);

    game.Process(curPlayer, AttackTask(curField[0], opField[0]));
    CHECK_EQ(opField[0]->HasReborn(), false);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}