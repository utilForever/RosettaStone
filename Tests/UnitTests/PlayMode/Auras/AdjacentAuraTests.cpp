// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Auras/AdjacentAura.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[AdjacentAura] - Invalid owner throws")
{
    AdjacentAura aura("EX1_162o");

    CHECK_THROWS(aura.Activate(nullptr));
    CHECK_THROWS(aura.Clone(nullptr));
}

TEST_CASE("[AdjacentAura] - Clone")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    FieldZone& field = *(curPlayer->GetFieldZone());

    TestUtils::PlayMinionCard(curPlayer, Cards::FindCardByName("Wisp"));
    TestUtils::PlayMinionCard(curPlayer, Cards::FindCardByName("Wisp"));

    AdjacentAura aura("EX1_162o");
    aura.Activate(field[0]);

    field[0]->ongoingEffect->Clone(field[1]);
    CHECK_NE(field[1]->ongoingEffect, nullptr);
}
