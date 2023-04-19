// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;

TEST_CASE("[Game] - GetPlayers")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game{ config };

    const Player* player1 = game.GetPlayer1();
    CHECK_EQ(player1->playerType, PlayerType::PLAYER1);

    const Player* player2 = game.GetPlayer2();
    CHECK_EQ(player2->playerType, PlayerType::PLAYER2);
}

TEST_CASE("[Game] - CurOpPlayer")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game1;
    game1.SetCurrentPlayer(PlayerType::PLAYER2);
    CHECK_EQ(game1.GetCurrentPlayer()->playerType, PlayerType::PLAYER2);
    CHECK_EQ(game1.GetOpponentPlayer()->playerType, PlayerType::PLAYER1);

    Game game2{ config };
    CHECK_EQ(game2.GetOpponentPlayer()->playerType, PlayerType::PLAYER2);

    config.startPlayer = PlayerType::PLAYER2;

    Game game3{ config };
    CHECK_EQ(game3.GetOpponentPlayer()->playerType, PlayerType::PLAYER1);
}

TEST_CASE("[Game] - Turn")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    auto* curPlayer = game.GetCurrentPlayer();
    auto* opPlayer = game.GetOpponentPlayer();

    CHECK_EQ(game.GetTurn(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(game.GetTurn(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(game.GetTurn(), 3);

    game.SetTurn(30);
    CHECK_EQ(game.GetTurn(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(game.GetTurn(), 31);
}

TEST_CASE("[Game] - GameOver_Player1Won")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
    opPlayer->GetHero()->SetDamage(29);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));

    CHECK_EQ(game.state, State::COMPLETE);
    CHECK_EQ(curPlayer->playState, PlayState::WON);
    CHECK_EQ(opPlayer->playState, PlayState::LOST);
}

TEST_CASE("[Game] - GameOver_Player2Won")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER2;
    config.doFillDecks = true;
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
    opPlayer->GetHero()->SetDamage(29);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));

    CHECK_EQ(game.state, State::COMPLETE);
    CHECK_EQ(curPlayer->playState, PlayState::WON);
    CHECK_EQ(opPlayer->playState, PlayState::LOST);
}

TEST_CASE("[Game] - GameOver_Tied")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
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
    curPlayer->GetHero()->SetDamage(29);
    opPlayer->GetHero()->SetDamage(29);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hellfire"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(game.state, State::COMPLETE);
    CHECK_EQ(curPlayer->playState, PlayState::TIED);
    CHECK_EQ(opPlayer->playState, PlayState::TIED);
}