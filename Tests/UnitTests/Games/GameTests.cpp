// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Policies/BasicPolicy.hpp>
#include <Rosetta/Tasks/PlayerTasks/ChooseTask.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;

struct MulliganTestPolicy : BasicPolicy {
    TaskMeta RequireMulligan(Player& player) override {
        return TaskMeta(TaskMetaTrait(TaskID::MULLIGAN), std::vector<size_t>());
    }
};

TEST(Game, Mulligan)
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.skipMulligan = false;
    config.autoRun = false;

    Game game(config);
    game.StartGame();

    auto& curPlayer = game.GetCurrentPlayer();
    auto& opPlayer = game.GetOpponentPlayer();

    MulliganTestPolicy policy;
    curPlayer.SetPolicy(&policy);
    opPlayer.SetPolicy(&policy);

    game.nextStep = Step::BEGIN_MULLIGAN;
    GameManager::ProcessNextStep(game, game.nextStep);
}