// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Games/Game.hpp>

using namespace RosettaStone;

TEST(Generic, GetZone)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();

    EXPECT_EQ(&curPlayer.GetDeckZone(),
              Generic::GetZone(curPlayer, ZoneType::DECK));
    EXPECT_EQ(&curPlayer.GetFieldZone(),
              Generic::GetZone(curPlayer, ZoneType::PLAY));
    EXPECT_EQ(&curPlayer.GetGraveyardZone(),
              Generic::GetZone(curPlayer, ZoneType::GRAVEYARD));
    EXPECT_EQ(&curPlayer.GetHandZone(),
              Generic::GetZone(curPlayer, ZoneType::HAND));
    EXPECT_EQ(&curPlayer.GetSecretZone(),
              Generic::GetZone(curPlayer, ZoneType::SECRET));
    EXPECT_EQ(&curPlayer.GetSetasideZone(),
              Generic::GetZone(curPlayer, ZoneType::SETASIDE));
    EXPECT_EQ(nullptr, Generic::GetZone(curPlayer, ZoneType::INVALID));
    EXPECT_EQ(nullptr, Generic::GetZone(curPlayer, ZoneType::REMOVEDFROMGAME));
}

TEST(Generic, ChoiceMulligan)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();

    std::vector<std::size_t> curChoices, opChoices;
    
    auto curHand = curPlayer.GetHandZone().GetAll();
    auto opHand = opPlayer.GetHandZone().GetAll();

    for (auto card : curHand)
    {
        curChoices.push_back(card->id);
    }
    for (auto card : opHand)
    {
        opChoices.push_back(card->id);
    }

    Choice curChoice, opChoice;

    curChoice.choiceAction = ChoiceAction::HAND;
    curChoice.choices = curChoices;
    curChoice.choiceType = ChoiceType::MULLIGAN;

    opChoice.choiceAction = ChoiceAction::HAND;
    opChoice.choices = opChoices;
    opChoice.choiceType = ChoiceType::MULLIGAN;

    curPlayer.choice = curChoice;
    opPlayer.choice = opChoice;

    int curHandCount = curPlayer.GetHandZone().GetCount();
    int opHandCount = opPlayer.GetHandZone().GetCount();

    Generic::ChoiceMulligan(curPlayer, curChoices);
    Generic::ChoiceMulligan(opPlayer, opChoices);

    EXPECT_EQ(curHandCount, curPlayer.GetHandZone().GetCount());
    EXPECT_EQ(opHandCount, opPlayer.GetHandZone().GetCount());

    EXPECT_EQ(curPlayer.choice, std::nullopt);
    EXPECT_EQ(opPlayer.choice, std::nullopt);
}