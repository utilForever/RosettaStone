// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;

TEST(SecretZone, Exist)
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();

    Entity* entity1 = Entity::GetFromCard(
        curPlayer, Cards::GetInstance().FindCardByName("Snipe"), std::nullopt,
        &curPlayer.GetSecretZone());
    curPlayer.GetSecretZone().Add(*entity1);

    Entity* entity2 = Entity::GetFromCard(
        curPlayer, Cards::GetInstance().FindCardByName("Counterspell"),
        std::nullopt, &curPlayer.GetHandZone());
    curPlayer.GetHandZone().Add(*entity2);

    EXPECT_EQ(curPlayer.GetSecretZone().Exist(*entity1), true);
    EXPECT_EQ(curPlayer.GetSecretZone().Exist(*entity2), false);
}