// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
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