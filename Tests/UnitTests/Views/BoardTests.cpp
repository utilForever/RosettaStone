// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Views/Board.hpp>

using namespace RosettaStone;

TEST(Board, RefCopyFrom)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    auto board1 = new Board(game, curPlayer->playerType);
    const auto board2 = new Board(game, opPlayer->playerType);

    board1->RefCopyFrom(*board2);
    EXPECT_EQ(board1->GetViewType(), PlayerType::PLAYER2);
    EXPECT_EQ(board1->GetCurrentPlayer()->playerType, PlayerType::PLAYER1);
}

TEST(Board, CreateView)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();

    curPlayer->GetHero()->SetAttack(2);
    curPlayer->GetHero()->SetArmor(3);

    opPlayer->GetHero()->SetAttack(1);
    opPlayer->GetHero()->SetArmor(2);

    const Board board1(game, curPlayer->playerType);
    const Board board2(game, opPlayer->playerType);

    auto reducedBoard1 = board1.CreateView();
    EXPECT_EQ(reducedBoard1.GetMyHero().attack, 2);
    EXPECT_EQ(reducedBoard1.GetMyHero().armor, 3);

    auto reducedBoard2 = board2.CreateView();
    EXPECT_EQ(reducedBoard2.GetMyHero().attack, 1);
    EXPECT_EQ(reducedBoard2.GetMyHero().armor, 2);
}

TEST(Board, RevealHiddenInfoForSimulation)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    game.step = Step::BEGIN_DRAW;
    game.nextStep = Step::MAIN_ACTION;

    const Board board(game, game.GetCurrentPlayer()->playerType);
    EXPECT_EQ(game.step, board.RevealHiddenInfoForSimulation().step);
    EXPECT_EQ(game.nextStep, board.RevealHiddenInfoForSimulation().nextStep);
}