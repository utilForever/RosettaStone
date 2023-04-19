// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace TestUtils;

TEST_CASE("[Character] - Health")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    PlayMinionCard(curPlayer, &card1);
    CHECK_EQ(curField[0]->GetHealth(), 6);

    curField[0]->SetDamage(2);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    curField[0]->SetBaseHealth(8);
    CHECK_EQ(curField[0]->GetDamage(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 6);
}

TEST_CASE("[Character] - MaxHealth")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    PlayMinionCard(curPlayer, &card1);
    CHECK_EQ(curField[0]->GetBaseHealth(), 6);

    curField[0]->SetDamage(2);
    CHECK_EQ(curField[0]->GetBaseHealth(), 6);

    curField[0]->SetBaseHealth(8);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->GetBaseHealth(), 8);
}

TEST_CASE("[Character] - SpellPower")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    PlayMinionCard(curPlayer, &card1);
    CHECK_EQ(curField[0]->GetSpellPower(), 0);

    curField[0]->SetSpellPower(4);
    CHECK_EQ(curField[0]->GetSpellPower(), 4);
}