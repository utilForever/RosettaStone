// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Tasks/PlayerTasks/ChooseTask.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;

TEST(Game, Mulligan)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = false;

    Game game(config);
    game.StartGame();

    auto& curPlayer = game.GetCurrentPlayer();
    auto& opPlayer = game.GetOpponentPlayer();

    Task::Run(curPlayer,
              ChooseTask::Mulligan(curPlayer, std::vector<std::size_t>()));
    Task::Run(opPlayer,
              ChooseTask::Mulligan(opPlayer, std::vector<std::size_t>()));

    game.nextStep = Step::MAIN_BEGIN;
    GameManager::ProcessNextStep(game, game.nextStep);
}