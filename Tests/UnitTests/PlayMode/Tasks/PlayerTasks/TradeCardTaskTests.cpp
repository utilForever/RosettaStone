// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/TradeCardTask.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace TestUtils;

TEST_CASE("[TradeCardTask] - Default")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Restless Mummy");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Impatient Shopkeep"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, TradeCardTask(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Wisp");

    curPlayer->SetUsedMana(10);
    CHECK_EQ(curPlayer->GetRemainingMana(), 0);

    game.Process(curPlayer, TradeCardTask(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 0);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Wisp");

    curPlayer->SetUsedMana(0);
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);

    game.Process(curPlayer, TradeCardTask(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Restless Mummy");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, TradeCardTask(curHand[6]));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[6]->card->name, "Impatient Shopkeep");
}