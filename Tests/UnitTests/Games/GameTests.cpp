// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Policies/BasicPolicy.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;

struct MulliganTestPolicy : BasicPolicy
{
    TaskMeta RequireMulligan(Player&) override
    {
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
    curPlayer.policy = &policy;
    opPlayer.policy = &policy;

    game.nextStep = Step::BEGIN_MULLIGAN;
    GameManager::ProcessNextStep(game, game.nextStep);
}

TEST(Game, GameOver)
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
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);
    opPlayer.GetHero()->SetDamage(29);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    game.Process(PlayCardTask::Minion(curPlayer, card1));
    game.Process(AttackTask(card1, opPlayer.GetHero()));

    EXPECT_EQ(game.state, State::COMPLETE);
    EXPECT_EQ(curPlayer.playState, PlayState::WON);
    EXPECT_EQ(opPlayer.playState, PlayState::LOST);
}