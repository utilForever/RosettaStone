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

    Player& curPlayer = game.GetCurrentPlayer();

    Entity* entity1 = Entity::GetFromCard(
        curPlayer, Cards::GetInstance().FindCardByName("Flame Imp"),
        std::nullopt, &curPlayer.GetFieldZone());
    curPlayer.GetFieldZone().Add(*entity1);

    Entity* entity2 = Entity::GetFromCard(
        curPlayer, Cards::GetInstance().FindCardByName("Worthless Imp"),
        std::nullopt, &curPlayer.GetFieldZone());
    curPlayer.GetFieldZone().Add(*entity2);

    const FieldZone& curField = curPlayer.GetFieldZone();
    auto minions = curField.GetAll();

    EXPECT_EQ(minions[0]->card->name, "Flame Imp");
    EXPECT_EQ(minions[1]->card->name, "Worthless Imp");
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

    Player& curPlayer = game.GetCurrentPlayer();

    Entity* entity1 = Entity::GetFromCard(
        curPlayer, Cards::GetInstance().FindCardByName("Flame Imp"),
        std::nullopt, &curPlayer.GetFieldZone());
    curPlayer.GetFieldZone().Add(*entity1);

    Entity* entity2 = Entity::GetFromCard(
        curPlayer, Cards::GetInstance().FindCardByName("Worthless Imp"),
        std::nullopt, &curPlayer.GetFieldZone());
    curPlayer.GetFieldZone().Add(*entity2);

    auto character1 = dynamic_cast<Character*>(entity1);
    auto character2 = dynamic_cast<Character*>(entity2);

    EXPECT_EQ(curPlayer.GetFieldZone().FindIndex(*character1), 0);
    EXPECT_EQ(curPlayer.GetFieldZone().FindIndex(*character2), 1);
}