// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;

TEST_CASE("[SecretZone] - Exist")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();

    Playable* playable1 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Snipe"),
                            std::nullopt, curPlayer->GetSecretZone());
    curPlayer->GetSecretZone()->Add(playable1);

    Playable* playable2 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Counterspell"),
                            std::nullopt, curPlayer->GetHandZone());
    curPlayer->GetHandZone()->Add(playable2);

    CHECK_EQ(curPlayer->GetSecretZone()->Exist(playable1), true);
    CHECK_EQ(curPlayer->GetSecretZone()->Exist(playable2), false);
}