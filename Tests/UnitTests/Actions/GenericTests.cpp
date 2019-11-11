// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

using namespace RosettaStone;

TEST(Generic, ShuffleIntoDeck)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Playable* coinCard =
        Entity::GetFromCard(curPlayer, Cards::FindCardByID("GAME_005"),
                            std::nullopt, curPlayer->GetHandZone());

    Generic::ShuffleIntoDeck(curPlayer, coinCard);
    EXPECT_EQ(curPlayer->GetDeckZone()->GetCount(), 1);
    EXPECT_EQ((*curPlayer->GetDeckZone())[0]->card->id, "GAME_005");
}

TEST(Generic, ShuffleIntoDeck_Full)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Playable* coinCard =
        Entity::GetFromCard(curPlayer, Cards::FindCardByID("GAME_005"),
                            std::nullopt, curPlayer->GetHandZone());

    for (std::size_t i = 0; i < MAX_DECK_SIZE; ++i)
    {
        Playable* tempCard =
            Entity::GetFromCard(curPlayer, Cards::FindCardByID("GAME_005"),
                                std::nullopt, curPlayer->GetHandZone());
        curPlayer->GetDeckZone()->Add(tempCard);
    }

    Generic::ShuffleIntoDeck(curPlayer, coinCard);
    EXPECT_EQ(curPlayer->GetDeckZone()->GetCount(), MAX_DECK_SIZE);
}

TEST(Generic, GetZone)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();

    EXPECT_EQ(curPlayer->GetDeckZone(),
              Generic::GetZone(curPlayer, ZoneType::DECK));
    EXPECT_EQ(curPlayer->GetFieldZone(),
              Generic::GetZone(curPlayer, ZoneType::PLAY));
    EXPECT_EQ(curPlayer->GetGraveyardZone(),
              Generic::GetZone(curPlayer, ZoneType::GRAVEYARD));
    EXPECT_EQ(curPlayer->GetHandZone(),
              Generic::GetZone(curPlayer, ZoneType::HAND));
    EXPECT_EQ(curPlayer->GetSecretZone(),
              Generic::GetZone(curPlayer, ZoneType::SECRET));
    EXPECT_EQ(curPlayer->GetSetasideZone(),
              Generic::GetZone(curPlayer, ZoneType::SETASIDE));
    EXPECT_EQ(nullptr, Generic::GetZone(curPlayer, ZoneType::INVALID));
    EXPECT_EQ(nullptr, Generic::GetZone(curPlayer, ZoneType::REMOVEDFROMGAME));
}