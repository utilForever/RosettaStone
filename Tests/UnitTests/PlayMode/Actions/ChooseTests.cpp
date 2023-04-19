// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Choose] - ChoiceMulligan")
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
    Player* opPlayer = game.GetOpponentPlayer();

    const std::vector<int> curChoices, opChoices;

    curPlayer->choice = new Choice(curPlayer);
    curPlayer->choice->choiceAction = ChoiceAction::HAND;
    curPlayer->choice->choices = curChoices;
    curPlayer->choice->choiceType = ChoiceType::MULLIGAN;

    opPlayer->choice = new Choice(opPlayer);
    opPlayer->choice->choiceAction = ChoiceAction::HAND;
    opPlayer->choice->choices = opChoices;
    opPlayer->choice->choiceType = ChoiceType::MULLIGAN;

    int curHandCount = curPlayer->GetHandZone()->GetCount();
    int opHandCount = opPlayer->GetHandZone()->GetCount();

    Generic::ChoiceMulligan(curPlayer, curChoices);
    Generic::ChoiceMulligan(opPlayer, opChoices);

    CHECK_EQ(curHandCount, curPlayer->GetHandZone()->GetCount());
    CHECK_EQ(opHandCount, opPlayer->GetHandZone()->GetCount());

    CHECK_EQ(curPlayer->choice, nullptr);
    CHECK_EQ(opPlayer->choice, nullptr);
}