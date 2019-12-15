// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;

TEST(FieldZone, GetAll)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

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

    EXPECT_EQ(minions[0]->card->name, "Flame Imp");
    EXPECT_EQ(minions[1]->card->name, "Wisp");
}

TEST(FieldZone, FindIndex)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

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

    Playable* playable3 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Wisp"),
                            std::nullopt, curPlayer->GetFieldZone());

    auto character1 = dynamic_cast<Minion*>(playable1);
    auto character2 = dynamic_cast<Minion*>(playable2);
    auto character3 = dynamic_cast<Minion*>(playable3);

    EXPECT_EQ(curField.FindIndex(character1), 0);
    EXPECT_EQ(curField.FindIndex(character2), 1);
    EXPECT_EQ(curField.FindIndex(character3), -1);
}