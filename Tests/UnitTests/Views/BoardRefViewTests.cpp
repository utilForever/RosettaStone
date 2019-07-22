// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Views/BoardRefView.hpp>

using namespace RosettaStone;

TEST(BoardRefView, GetFatigueDamage)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    curPlayer.GetHero()->fatigue = 3;
    opPlayer.GetHero()->fatigue = 5;

    BoardRefView board(game, curPlayer.playerType);
    EXPECT_EQ(board.GetFatigueDamage(PlayerType::PLAYER1), 3);
    EXPECT_EQ(board.GetFatigueDamage(PlayerType::PLAYER2), 5);
}

TEST(BoardRefView, GetTotalMana)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    curPlayer.SetTotalMana(4);
    opPlayer.SetTotalMana(7);

    BoardRefView board(game, curPlayer.playerType);
    EXPECT_EQ(board.GetTotalMana(PlayerType::PLAYER1), 4);
    EXPECT_EQ(board.GetTotalMana(PlayerType::PLAYER2), 7);
}

TEST(BoardRefView, GetUsedMana)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    curPlayer.SetUsedMana(4);
    opPlayer.SetUsedMana(3);

    BoardRefView board(game, curPlayer.playerType);
    EXPECT_EQ(board.GetUsedMana(PlayerType::PLAYER1), 4);
    EXPECT_EQ(board.GetUsedMana(PlayerType::PLAYER2), 3);
}

TEST(BoardRefView, GetTemporaryMana)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    curPlayer.SetTemporaryMana(2);
    opPlayer.SetTemporaryMana(5);

    BoardRefView board(game, curPlayer.playerType);
    EXPECT_EQ(board.GetTemporaryMana(PlayerType::PLAYER1), 2);
    EXPECT_EQ(board.GetTemporaryMana(PlayerType::PLAYER2), 5);
}

TEST(BoardRefView, GetOverloadOwed)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    curPlayer.SetOverloadOwed(6);
    opPlayer.SetOverloadOwed(3);

    BoardRefView board(game, curPlayer.playerType);
    EXPECT_EQ(board.GetOverloadOwed(PlayerType::PLAYER1), 6);
    EXPECT_EQ(board.GetOverloadOwed(PlayerType::PLAYER2), 3);
}

TEST(BoardRefView, GetOverloadLocked)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    curPlayer.SetOverloadLocked(7);
    opPlayer.SetOverloadLocked(2);

    BoardRefView board(game, curPlayer.playerType);
    EXPECT_EQ(board.GetOverloadLocked(PlayerType::PLAYER1), 7);
    EXPECT_EQ(board.GetOverloadLocked(PlayerType::PLAYER2), 2);
}

TEST(BoardRefView, GetRemainingMana)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    curPlayer.SetTotalMana(4);
    opPlayer.SetTotalMana(7);
    curPlayer.SetUsedMana(4);
    opPlayer.SetUsedMana(3);

    BoardRefView board(game, curPlayer.playerType);
    EXPECT_EQ(board.GetRemainingMana(PlayerType::PLAYER1), 0);
    EXPECT_EQ(board.GetRemainingMana(PlayerType::PLAYER2), 4);
}

TEST(BoardRefView, GetHero)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    BoardRefView board1(game, curPlayer.playerType);
    EXPECT_EQ(board1.GetHero()->card->id, "HERO_01");

    BoardRefView board2(game, opPlayer.playerType);
    EXPECT_EQ(board2.GetHero()->card->id, "HERO_03");
}

TEST(BoardRefView, GetOpponentHero)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    BoardRefView board1(game, curPlayer.playerType);
    EXPECT_EQ(board1.GetHero()->card->id, "HERO_01");

    BoardRefView board2(game, opPlayer.playerType);
    EXPECT_EQ(board2.GetHero()->card->id, "HERO_03");
}

TEST(BoardRefView, GetHeroPower)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    BoardRefView board(game, game.GetCurrentPlayer().playerType);
    EXPECT_EQ(board.GetHeroPower(PlayerType::PLAYER1)->card->id, "CS2_102");
    EXPECT_EQ(board.GetHeroPower(PlayerType::PLAYER2)->card->id, "CS2_083b");
}

TEST(BoardRefView, GetWeapon)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    BoardRefView board(game, game.GetCurrentPlayer().playerType);
    EXPECT_EQ(board.GetWeapon(PlayerType::PLAYER1), nullptr);
    EXPECT_EQ(board.GetWeapon(PlayerType::PLAYER2), nullptr);
}

TEST(BoardRefView, GetHandCards)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    BoardRefView board1(game, curPlayer.playerType);
    EXPECT_EQ(board1.GetHandCards().size(), 4u);

    BoardRefView board2(game, opPlayer.playerType);
    EXPECT_EQ(board2.GetHandCards().size(), 5u);
}

//TEST(BoardRefView, GetOpponentHandCards)
//{
//    GameConfig config;
//    config.player1Class = CardClass::WARRIOR;
//    config.player2Class = CardClass::ROGUE;
//    config.startPlayer = PlayerType::PLAYER1;
//    config.doFillDecks = true;
//    config.autoRun = false;
//
//    Game game(config);
//    game.StartGame();
//    game.ProcessUntil(Step::MAIN_START);
//
//    Player& curPlayer = game.GetCurrentPlayer();
//    Player& opPlayer = game.GetOpponentPlayer();
//
//    BoardRefView board1(game, curPlayer.playerType);
//    EXPECT_EQ(board1.GetOpponentHandCards().size(), 5u);
//    EXPECT_EQ(board1.GetOpponentHandCards().at(0)->card->id, "INVALID");
//
//    BoardRefView board2(game, opPlayer.playerType);
//    EXPECT_EQ(board2.GetOpponentHandCards().size(), 4u);
//    EXPECT_EQ(board2.GetOpponentHandCards().at(0)->card->id, "INVALID");
//}