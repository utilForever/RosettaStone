// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;

TEST_CASE("[FieldZone] - GetAll")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    auto& curField = *(curPlayer->GetFieldZone());

    Playable* playable1 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Flame Imp"),
                            std::nullopt, curPlayer->GetFieldZone());
    curField.Add(playable1);

    Playable* playable2 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Wisp"),
                            std::nullopt, curPlayer->GetFieldZone());
    curField.Add(playable2);

    auto minions = curField.GetAll();

    CHECK_EQ(minions[0]->card->name, "Flame Imp");
    CHECK_EQ(minions[1]->card->name, "Wisp");
}