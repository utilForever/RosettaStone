// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Views/Board.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Board] - RefCopyFrom")
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

    auto board1 = new Board(game, curPlayer->playerType);
    const auto board2 = new Board(game, opPlayer->playerType);

    board1->RefCopyFrom(*board2);
    CHECK_EQ(board1->GetViewType(), PlayerType::PLAYER2);
    CHECK_EQ(board1->GetCurrentPlayer()->playerType, PlayerType::PLAYER1);
}

TEST_CASE("[Board] - CreateView")
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

    curPlayer->GetHero()->SetAttack(2);
    curPlayer->GetHero()->SetArmor(3);

    opPlayer->GetHero()->SetAttack(1);
    opPlayer->GetHero()->SetArmor(2);

    const Board board1(game, curPlayer->playerType);
    const Board board2(game, opPlayer->playerType);

    auto reducedBoard1 = board1.CreateView();
    CHECK_EQ(reducedBoard1.GetMyHero().attack, 2);
    CHECK_EQ(reducedBoard1.GetMyHero().armor, 3);

    auto reducedBoard2 = board2.CreateView();
    CHECK_EQ(reducedBoard2.GetMyHero().attack, 1);
    CHECK_EQ(reducedBoard2.GetMyHero().armor, 2);
}

TEST_CASE("[Board] - RevealHiddenInfoForSimulation")
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

    game.step = Step::BEGIN_DRAW;
    game.nextStep = Step::MAIN_ACTION;

    const Board board(game, game.GetCurrentPlayer()->playerType);
    CHECK_EQ(game.step, board.RevealHiddenInfoForSimulation().step);
    CHECK_EQ(game.nextStep, board.RevealHiddenInfoForSimulation().nextStep);
}