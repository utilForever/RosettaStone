// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;

TEST_CASE("[HandZone] - FindIndex")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();

    Playable* playable1 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Fireball"),
                            std::nullopt, curPlayer->GetHandZone());
    curPlayer->GetHandZone()->Add(playable1);

    Playable* playable2 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Flamestrike"),
                            std::nullopt, curPlayer->GetHandZone());
    curPlayer->GetHandZone()->Add(playable2);

    Playable* playable3 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Flamestrike"),
                            std::nullopt, curPlayer->GetHandZone());

    CHECK_EQ(curPlayer->GetHandZone()->FindIndex(playable1), 0);
    CHECK_EQ(curPlayer->GetHandZone()->FindIndex(playable2), 1);
    CHECK_EQ(curPlayer->GetHandZone()->FindIndex(playable3), -1);
}